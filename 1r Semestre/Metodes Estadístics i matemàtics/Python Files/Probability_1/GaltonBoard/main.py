#
# Source code from https://medium.com/explorations-in-python/galton-board-in-python-3309584934bd
#
import galtonboard
import galtonboardview
import sys
import os


def main():

    """
    Creates and runs a GaltonBoard index object
    """

    gb = galtonboard.GaltonBoard(7,
                                 40,
                                 galtonboardview.on_init,
                                 galtonboardview.on_ball_moved,
                                 galtonboardview.on_total_changed)

    gb.initialize()

    #os.system('setterm -cursor off')

    gb.start()

    #os.system('setterm -cursor on')


main() 