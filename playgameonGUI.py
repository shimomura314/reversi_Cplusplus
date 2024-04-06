"""
オセロアプリを起動するためのファイル.
    - bitbord : オセロの手続きを設定
    - display : GUIを設定
    - strategy : CPUの戦略を定義
pyinstaller playgameonGUI.py --onefile --noconsoleでexe化
"""

import wx

from bitboard import othello
from display import MyFrame


if __name__ == "__main__":
    game = othello.Othello()

    application = wx.App()
    frame = MyFrame(title="Othello Game", othello=game)

    frame.Center()
    frame.Show()
    application.MainLoop()
    wx.Exit()
