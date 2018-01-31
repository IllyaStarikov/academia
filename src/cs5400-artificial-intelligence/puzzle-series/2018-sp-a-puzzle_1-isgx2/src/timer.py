#!/usr/local/bin/python3
#
# timer.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/24/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

from datetime import datetime


class Timer():
    __start_time, __stop_time = None, None

    def start(self):
        """Starts the timer"""
        self.__start_time = datetime.now()

    def stop(self):
        """Stops the timer"""
        self.__stop_time = datetime.now()

    @property
    def difference(self):
        """Calculate the difference between the start time and the stop time.

        Returns:
            float: The amount of seconds that have pass between the timer starting
            and the timer stopping.
        """
        delta = self.__stop_time - self.__start_time
        return delta.total_seconds()
