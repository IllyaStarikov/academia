#!/usr/local/bin/python3
#
# logger.py
# source
#
# Created by Illya Starikov on 01/29/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

import datetime
import os
from enum import Enum
import progressbar


class LogPriority(Enum):
    ERROR = 0,
    INFO = 1,
    PROGRESS = 2

    def __str__(self):
        descriptors = {
            LogPriority.ERROR: "Error",
            LogPriority.INFO: "Info",
            LogPriority.PROGRESS: "Progress"
        }

        return descriptors[self]


class Logger():
    def __init__(self, log_directory='./log', should_show_progress_bar=False, max_progress_bar=None):
        self.should_show_progress_bar = should_show_progress_bar
        self.max_progress_bar = max_progress_bar

        if should_show_progress_bar:
            self.__bar = progressbar.ProgressBar(maxval=max_progress_bar, widgets=[progressbar.Bar('=', '[', ']'), ' ', progressbar.Percentage()])
            self.__bar.start()
        else:
            self.__bar = None

        if __debug__:
            self.filename = os.path.join(log_directory, self.generate_filename())
            self.create_initial_log_file(log_directory)

    def configure_progress_bar(self, max_progress_bar):
        self.max_progress_bar = max_progress_bar

        self.__bar = progressbar.ProgressBar(maxval=max_progress_bar, widgets=[progressbar.Bar('=', '[', ']'), ' ', progressbar.Percentage()])
        self.__bar.start()

    def generate_filename(self):
        if __debug__:
            current_date = datetime.datetime.now()
            date_description = current_date.strftime('%d-%m-%y')
            time_description = current_date.strftime('%H-%M')

            return "log_{}_{}.txt".format(date_description, time_description)

    def create_initial_log_file(self, directory_name):
        if __debug__:
            if not os.path.isdir(directory_name) or not os.path.exists(directory_name):
                os.makedirs(directory_name)

            with open(self.filename, 'w') as file_handler:
                file_handler.write('Log Created On {}'.format(datetime.datetime.now()))

    def log(self, message, status):
        if self.__bar and status == LogPriority.PROGRESS:
            if message > self.max_progress_bar:
                message = self.max_progress_bar

            self.__bar.update(message)

        if __debug__:
            time_description = datetime.datetime.now().strftime('%H-%M')

            with open(self.filename, 'a') as file_handler:
                if status != LogPriority.PROGRESS:
                    file_handler.write("[{}] {}: {}.\n".format(status, time_description, message))

            if status == LogPriority.ERROR:
                print("[{}] {}: {}.".format(status, time_description, message))

    def stop_progress_bar(self):
        self.__bar.finish()


logger = Logger()
