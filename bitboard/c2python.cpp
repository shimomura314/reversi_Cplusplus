// cmake --build .  

#include "othello.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(othello, m) {
    m.doc() = "Python module for C++ class and functions from main.cpp";

    py::class_<BitBoard>(m, "BitBoard")
        .def(py::init<>())

        .def_static("bit_count", &BitBoard::bit_count, py::arg("x"))
        .def_static(
            "check_surround", 
            &BitBoard::check_surround, py::arg("x"), py::arg("direction"))
        .def_static(
            "count_disks", &BitBoard::count_disks,
            py::arg("b_board"), py::arg("w_board"))
        .def_static(
            "reversible_area", &BitBoard::reversible_area,
            py::arg("turn"), py::arg("b_board"), py::arg("w_board"))
        .def_static(
            "reversible_area_list", &BitBoard::reversible_area_list,
            py::arg("turn"), py::arg("b_board"), py::arg("w_board"))
        .def_static(
            "is_reversible", &BitBoard::is_reversible,
            py::arg("put_loc"), py::arg("turn"),
            py::arg("b_board"), py::arg("w_board"))
        .def_static(
            "turn_playable", &BitBoard::turn_playable,
            py::arg("turn"), py::arg("b_board"), py::arg("w_board"))
        .def_static(
            "judge_game", &BitBoard::judge_game,
            py::arg("b_board"), py::arg("w_board"))

        .def("return_board", &BitBoard::return_board)
        .def("return_turn", &BitBoard::return_turn)
        .def("return_result", &BitBoard::return_result)
        .def("display_board", &BitBoard::display_board)
        .def(
            "load_board", &BitBoard::load_board,
            py::arg("b_board"), py::arg("w_board"))
        .def("load_state", &BitBoard::load_state)
        .def("save_state", &BitBoard::save_state)
        .def("undo_turn", &BitBoard::undo_turn)
        .def("redo_turn", &BitBoard::redo_turn)

        .def_static(
            "simulate_play", &BitBoard::simulate_play,
            py::arg("turn"), py::arg("put_loc"),
            py::arg("b_board"), py::arg("w_board"))
        .def("play_turn", &BitBoard::play_turn, py::arg("put_loc"))
        .def("skip_turn", &BitBoard::skip_turn)
        .def("update_count", &BitBoard::update_count)
        .def("auto_mode", &BitBoard::auto_mode, py::arg("automode") = true)
        ;

    // Strategyクラスのバインディング
    py::class_<Strategy>(m, "Strategy")
        .def(py::init<const std::string&>(), py::arg("strategy") = "random")
        .def("set_strategy", &Strategy::set_strategy, py::arg("strategy"))
        .def("move", &Strategy::move, py::arg("board"))
        ;

    // Othelloクラスのバインディング
    py::class_<Othello, BitBoard>(m, "Othello") // BitBoardを基本クラスとして指定
        .def(py::init<uint8_t>(), py::arg("color") = 0)
        .def("return_player_clr", &Othello::return_player_clr)
        .def(
            "change_strategy", &Othello::change_strategy,
            py::arg("strategy"), py::arg("is_player") = false)
        .def("change_player", &Othello::change_player, py::arg("color"))
        .def("process_game", &Othello::process_game)
        // 他の必要なメンバ関数をここにバインド
        ;
}
