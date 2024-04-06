# pytest ./bitboard/_test_othello.py

import othello


def test_initialize():
    game = othello.Othello()
    assert game.return_board() == (34628173824, 68853694464)
    assert game.return_turn() == 0
    assert game.return_result() == 3

def test_bit_count():
    game = othello.Othello()
    assert game.bit_count(32) == 1
    assert game.bit_count(31) == 5

def test_check_surround():
    game = othello.Othello()
    assert game.check_surround(524288, 0) == 134217728
    assert game.check_surround(524288, 1) == 67108864
    assert game.check_surround(524288, 2) == 262144
    assert game.check_surround(524288, 3) == 1024
    assert game.check_surround(524288, 4) == 2048
    assert game.check_surround(524288, 5) == 4096
    assert game.check_surround(524288, 6) == 1048576
    assert game.check_surround(524288, 7) == 268435456

def test_count_disks():
    game = othello.Othello()
    assert game.count_disks() == (2, 2)
    assert game.count_disks(524281438, 95782216) == (21, 12)
    game.load_board(524281438, 95782216)
    assert game.count_disks() == (21, 12)

def test_reversible_area():
    game = othello.Othello()
    x = 0x0000000810000000
    y = 0x0000001008000000
    assert game.reversible_area(0, x, y) == 17729692631040
    assert game.reversible_area(1, x, y) == 8813810810880
    assert game.reversible_area_list(0, x, y) == [19, 26, 37, 44]
    assert game.reversible_area_list(1, x, y) == [20, 29, 34, 43]

# def test_is_reversible():
#     game = othello.Othello()
#     assert game.return_board() == (34628173824, 68853694464)

# def test_turn_playable():
#     game = othello.Othello()
#     assert game.return_board() == (34628173824, 68853694464)

# def test_simulate_playe():
#     game = othello.Othello()
#     assert game.return_board() == (34628173824, 68853694464)

# def test_play_turn():
#     game = othello.Othello()
#     assert game.return_board() == (34628173824, 68853694464)

# def test_judge_game():
#     game = othello.Othello()
#     assert game.return_board() == (34628173824, 68853694464)
