/*
 * Get one gray image using libdc1394 and store it as portable gray map
 *    (pgm). Based on 'samplegrab' from Chris Urmson
 *
 * Author: Sasha Petrenko <sap625@mst.edu>
 * Date: 11/5/2015
 * Code Documentation:
 * API Documentation: http://damien.douxchamps.net/ieee1394/libdc1394/
 *
 */

#pragma GCC diagnostic ignored "-fpermissive"

#include <stdio.h>
#include <stdint.h>
#include <dc1394/dc1394.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

#ifndef _WIN32
#include <unistd.h>
#endif

#define IMAGE_FILE_NAME "image.jpg"
#define IMAGE_EXTENSION ".jpg"
#define HERTZ 3

/*-----------------------------------------------------------------------
 *  Releases the cameras and exits
 *-----------------------------------------------------------------------*/
void cleanup_and_exit(dc1394camera_t *camera)
{
    dc1394_video_set_transmission(camera, DC1394_OFF);
    dc1394_capture_stop(camera);
    dc1394_camera_free(camera);
    exit(1);
}

int main(int argc, char *argv[])
{
    FILE* imagefile;
    dc1394camera_t *camera;
    int i;
    dc1394featureset_t features;
    dc1394framerates_t framerates;
    dc1394video_modes_t video_modes;
    dc1394framerate_t framerate;
    dc1394video_mode_t video_mode = 0;
    dc1394color_coding_t coding;
    unsigned int width, height;
    dc1394video_frame_t *frame;
    dc1394_t * d;
    dc1394camera_list_t * list;
    
    dc1394error_t err;
    
    char filehead[] = "image";
    char filesave[50] = "image00000";
    time_t time_start;
    char* c_time_string;
    float frequency = 1.0/HERTZ;
    
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 3000;
    
    time_start = time(NULL);
    
    if (time_start == ((time_t)-1))
    {
        printf("Failure to obtain the current time.\n");
    }
    
    d = dc1394_new ();
    if (!d)
        return 1;
    err=dc1394_camera_enumerate (d, &list);
    DC1394_ERR_RTN(err,"Failed to enumerate cameras");
    
    if (list->num == 0) {
        dc1394_log_error("No cameras found");
        return 1;
    }
    
    camera = dc1394_camera_new (d, list->ids[0].guid);
    if (!camera) {
        dc1394_log_error("Failed to initialize camera with guid %"PRIx64, list->ids[0].guid);
        return 1;
    }
    dc1394_camera_free_list (list);
    //printf("So far so good.");
    //printf("Using camera with GUID %"PRIx64"\n", camera->guid);
    
    /*-----------------------------------------------------------------------
     *  get the best video mode and highest framerate. This can be skipped
     *  if you already know which mode/framerate you want...
     *-----------------------------------------------------------------------*/
    // get video modes:
    err=dc1394_video_get_supported_modes(camera,&video_modes);
    DC1394_ERR_CLN_RTN(err,cleanup_and_exit(camera),"Can't get video modes");
    
    // select highest res mode:
    for (i=video_modes.num-1;i>=0;i--) {
        if (!dc1394_is_video_mode_scalable(video_modes.modes[i])) {
            dc1394_get_color_coding_from_video_mode(camera,video_modes.modes[i], &coding);
            if (coding==DC1394_COLOR_CODING_MONO8) {
                video_mode=video_modes.modes[i];
                break;
            }
        }
    }
    if (i < 0) {
        dc1394_log_error("Could not get a valid MONO8 mode");
        cleanup_and_exit(camera);
    }
    
    err=dc1394_get_color_coding_from_video_mode(camera, video_mode,&coding);
    DC1394_ERR_CLN_RTN(err,cleanup_and_exit(camera),"Could not get color coding");
    
    // get highest framerate
    err=dc1394_video_get_supported_framerates(camera,video_mode,&framerates);
    DC1394_ERR_CLN_RTN(err,cleanup_and_exit(camera),"Could not get framrates");
    framerate=framerates.framerates[framerates.num-1];
    
    printf("Setup Capture\n");
    
    /*-----------------------------------------------------------------------
     *  setup capture
     *-----------------------------------------------------------------------*/
    
    err=dc1394_video_set_iso_speed(camera, DC1394_ISO_SPEED_400);
    DC1394_ERR_CLN_RTN(err,cleanup_and_exit(camera),"Could not set iso speed");
    
    err=dc1394_video_set_mode(camera, video_mode);
    DC1394_ERR_CLN_RTN(err,cleanup_and_exit(camera),"Could not set video mode");
    
    err=dc1394_video_set_framerate(camera, framerate);
    DC1394_ERR_CLN_RTN(err,cleanup_and_exit(camera),"Could not set framerate");
    
    err=dc1394_capture_setup(camera,4, DC1394_CAPTURE_FLAGS_DEFAULT);
    DC1394_ERR_CLN_RTN(err,cleanup_and_exit(camera),"Could not setup camera-\nmake sure that the video mode and framerate are\nsupported by your camera");
    
    /*-----------------------------------------------------------------------
     *  report camera's features
     *-----------------------------------------------------------------------*/
    /*
     err=dc1394_feature_get_all(camera,&features);
     if (err!=DC1394_SUCCESS) {
     dc1394_log_warning("Could not get feature set");
     }
     else {
     dc1394_feature_print_all(&features, stdout);
     }
     */
    /*-----------------------------------------------------------------------
     *  have the camera start sending us data
     *-----------------------------------------------------------------------*/
    err=dc1394_video_set_transmission(camera, DC1394_ON);
    DC1394_ERR_CLN_RTN(err,cleanup_and_exit(camera),"Could not start camera iso transmission");
    
    
    // Main for loop
    
    for ( i = 1; i < 50; ++i) {
        printf("Start of iteration\n");
        
        while ( difftime(time(NULL),time_start) < frequency){
            nanosleep((const struct timespec[]){{0,3000L}}, NULL);;
        }
        
        time_start = time(NULL);
        
        /*-----------------------------------------------------------------------
         *  capture one frame
         *-----------------------------------------------------------------------*/
        err=dc1394_capture_dequeue(camera, DC1394_CAPTURE_POLICY_WAIT, &frame);
        DC1394_ERR_CLN_RTN(err,cleanup_and_exit(camera),"Could not capture a frame");
        
        printf("Captured frame\n");
        /*-----------------------------------------------------------------------
         *  save image as 'image.jpg'
         *-----------------------------------------------------------------------*/
        
        //count = i;
        //printf(count,"\n");
        
        //filesave = strcat(fileheader,count);
        sprintf(filesave, "image%d.jpg",i);
        puts(filesave);
        //printf(filesave,"\n");
        //imagefile=fopen(IMAGE_FILE_NAME, "wb");
        imagefile=fopen(filesave, "wb");
        
        if( imagefile == NULL) {
            perror( "Can't create '" IMAGE_FILE_NAME "'");
            cleanup_and_exit(camera);
        }
        
        dc1394_get_image_size_from_video_mode(camera, video_mode, &width, &height);
        printf("Get image size\n");
        
        fprintf(imagefile,"P5\n%u %u 255\n", width, height);
        printf("Fprintf\n");
        
        fwrite(frame->image, 1, height*width, imagefile);
        printf("Fwrite\n");
        
        fclose(imagefile);
        printf("Fclose\n");
        
        //printf("wrote: " IMAGE_FILE_NAME "\n");
        //printf("wrote: ", filesave, "\n");
        
        // End main for loop
        printf("End of iteration\n");
        err=dc1394_capture_enqueue(camera,frame);
        printf("Release thine buffah!\n");
        
    }
    
    
    /*-----------------------------------------------------------------------
     *  stop data transmission
     *-----------------------------------------------------------------------*/
    err=dc1394_video_set_transmission(camera,DC1394_OFF);
    DC1394_ERR_CLN_RTN(err,cleanup_and_exit(camera),"Could not stop the camera");
    printf("Camera Stopped\n");
    
    /*-----------------------------------------------------------------------
     *  close camera
     *-----------------------------------------------------------------------*/
    dc1394_video_set_transmission(camera, DC1394_OFF);
    dc1394_capture_stop(camera);
    dc1394_camera_free(camera);
    dc1394_free (d);
    printf("Camera Closed\n");
    
    return 0;
}
