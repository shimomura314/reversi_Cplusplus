"""
オセロアプリを起動するためのファイル.
    - bitbord : オセロのアルゴリズムを定義
    - display : GUIの表示を定義
    - matching: CPU同士の対戦を定義
    - strategy : CPUの戦略を定義

pyinstaller playgameonGUI.py --onefile --noconsole で exe 化
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
