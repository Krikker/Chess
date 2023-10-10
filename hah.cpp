#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

struct Piece {
    std::string name = "";
    std::string color = "";
    int y = -1;
    int x = -1;
};

class ChessBoard {
public:
    std::vector<std::vector<Piece>> board;
    std::vector<Piece> white;
    std::vector<Piece> black;
    ChessBoard() {

        board.resize(8, std::vector<Piece>(8));
    }
    void make() {

        white.clear();
        black.clear();
        board.clear();
        board.resize(8, std::vector<Piece>(8));

        board[0][0] = { "r", "White" ,0,0 };
        board[0][1] = { "n", "White" ,0,1 };
        board[0][2] = { "b", "White" ,0,2 };
        board[0][4] = { "k", "White" ,0,4 };
        board[0][5] = { "b", "White" ,0,5 };
        board[0][6] = { "n", "White" ,0,6 };
        board[0][7] = { "r", "White" ,0,7 };
        for (int i = 0; i < 8; i++) {
            board[1][i] = { "p", "White" ,1,i };
            if (i != 3) { white.push_back(board[0][i]); }
            white.push_back(board[1][i]);

        }

        board[7][0] = { "R", "Black" ,7,0 };
        board[7][1] = { "N", "Black" ,7,1 };
        board[7][2] = { "B", "Black" ,7,2 };
        board[7][4] = { "K", "Black" ,7,4 };
        board[7][5] = { "B", "Black" ,7,5 };
        board[7][6] = { "N", "Black" ,7,6 };
        board[7][7] = { "R", "Black" ,7,7 };
        for (int i = 0; i < 8; i++) {
            board[6][i] = { "P", "Black" ,6,i };
            if (i != 3) { black.push_back(board[7][i]); }
            black.push_back(board[6][i]);
        }

    }
    void printBoard() {
        std::cout << "   a  b  c  d  e  f  g  h" << std::endl;
        for (int i = 0; i < 8; i++) {
            std::cout << i + 1 << " ";
            for (int j = 0; j < 8; j++) {
                if (board[i][j].name.empty()) {
                    std::cout << "[ ]";
                }
                else {
                    if (board[i][j].name[1] != 'n') { std::cout << "[" << board[i][j].name[0] << "]"; }
                    else {
                        if (board[i][j].color == "White") { std::cout << "[n]"; }
                        else { {std::cout << "[N]"; }
                        }
                    }
                }
            }
            std::cout << std::endl;
        }
    }
    std::vector<std::vector<int>> move(Piece figure) {
        std::vector<std::vector<int>> moves;
        int x = figure.x;
        int y = figure.y;
        if (figure.name == "p" && y != 7) {
            if (board[y + 1][x].color == "") {
                moves.push_back(std::vector<int>{y + 1, x});
            }
            if (x != 7 && board[y + 1][x + 1].color == "Black") {
                moves.push_back(std::vector<int>{y + 1, x + 1});
            }
            if (x != 0 && board[y + 1][x - 1].color == "Black") {
                moves.push_back(std::vector<int>{y + 1, x - 1});
            }
        }
        if (figure.name == "P" && y != 0) {
            if (board[y - 1][x].color == "") {
                moves.push_back(std::vector<int>{y - 1, x});
            }
            if (x != 7 && board[y - 1][x + 1].color == "White") {
                moves.push_back(std::vector<int>{y - 1, x + 1});
            }
            if (x != 0 && board[y - 1][x - 1].color == "White") {
                moves.push_back(std::vector<int>{y - 1, x - 1});
            }
        }
        if (figure.name == "r" || figure.name == "R") {
            for (int i = 1; i < 8; i++) {
                if (y + i > 7 || board[y + i][x].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y + i, x});
                if (board[y + i][x].color == "") { continue; }
                break;
            }
            for (int i = 1; i < 8; i++) {
                if (y - i < 0 || board[y - i][x].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y - i, x});
                if (board[y - i][x].color == "") { continue; }
                break;
            }
            for (int i = 1; i < 8; i++) {
                if (x + i > 7 || board[y][x + i].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y, x + i});
                if (board[y][x + i].color == "") { continue; }
                break;
            }
            for (int i = 1; i < 8; i++) {
                if (x - i < 0 || board[y][x - i].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y, x - i});
                if (board[y][x - i].color == "") { continue; }
                break;
            }
        }
        if (figure.name == "n" || figure.name == "N") {
            for (int i = -2; i < 3; i++) {
                for (int j = -1; j < 2; j++) {
                    if (i * j != 0 && x + i >= 0 && y + 2 / i * j >= 0 && x + i < 8 &&
                        y + 2 / i * j < 8 && board[y + 2 / i * j][x + i].color != figure.color) {
                        moves.push_back(std::vector<int>{y + 2 / i * j, x + i});
                    }
                }
            }
        }
        if (figure.name == "b" || figure.name == "B") {
            for (int i = 1; i < 8; i++) {
                if (y + i > 7 || x - i < 0 || board[y + i][x - i].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y + i, x - i});
                if (board[y + i][x - i].color == "") { continue; }
                break;
            }
            for (int i = 1; i < 8; i++) {
                if (y - i < 0 || x + i > 7 || board[y - i][x + i].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y - i, x + i});
                if (board[y - i][x + i].color == "") { continue; }
                break;
            }
            for (int i = 1; i < 8; i++) {
                if (y + i > 7 || x + i > 7 || board[y + i][x + i].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y + i, x + i});
                if (board[y + i][x + i].color == "") { continue; }
                break;
            }
            for (int i = 1; i < 8; i++) {
                if (x - i < 0 || y - i < 0 || board[y - i][x - i].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y - i, x - i});
                if (board[y - i][x - i].color == "") { continue; }
                break;
            }
        }
        if (figure.name == "k" || figure.name == "K") {
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (i != 0 && j != 0 && x + i >= 0 && y + j >= 0 && x + i < 8 && y + j < 8 && board[y + j][x + i].color != figure.color) {
                        moves.push_back(std::vector<int>{y + j, x + i});
                    }
                }
            }
        }
        return moves;
    }
};

std::random_device rd;
std::mt19937 rng(rd());

int main() {
    setlocale(LC_ALL, "Russian");
    ChessBoard chessboard;
    chessboard.make();
    chessboard.printBoard();
    int steps;
    std::cout << "Введите нужное число ходов:";
    std::cin >> steps;
    std::vector<std::vector<int>> moves;
    bool t = 1;
    while (t) {
        chessboard.make();
        for (int i = 0; i < steps; i++) {
            if (chessboard.black.size() == 0 || chessboard.white.size() == 0) { break; }
            if (i % 2 == 1) {
                std::shuffle(chessboard.black.begin(), chessboard.black.end(), rng);
                moves = chessboard.move(chessboard.black[0]);
                std::shuffle(moves.begin(), moves.end(), rng);
                if (moves.size() == 0) {
                    continue;
                }
                chessboard.board[moves[0][0]][moves[0][1]] = chessboard.black[0];

                chessboard.board[chessboard.black[0].y][chessboard.black[0].x] = Piece();
                for (int j = 0; j < chessboard.white.size(); j++) {
                    if (chessboard.white[j].x == moves[0][1] && chessboard.white[j].y == moves[0][0]) {
                        chessboard.white[j] = chessboard.white[chessboard.white.size() - 1];
                        chessboard.white.pop_back();
                        break;
                    }
                }
                chessboard.black[0].x = moves[0][1];
                chessboard.black[0].y = moves[0][0];
            }
            else
            {
                std::shuffle(chessboard.white.begin(), chessboard.white.end(), rng);
                moves = chessboard.move(chessboard.white[0]);
                std::shuffle(moves.begin(), moves.end(), rng);
                if (moves.size() == 0) {
                    continue;
                }
                chessboard.board[moves[0][0]][moves[0][1]] = chessboard.white[0];
                chessboard.board[chessboard.white[0].y][chessboard.white[0].x] = Piece();
                for (int j = 0; j < chessboard.black.size(); j++) {
                    if (chessboard.black[j].x == moves[0][1] && chessboard.black[j].y == moves[0][0]) {
                        chessboard.black[j] = chessboard.black[chessboard.black.size() - 1];
                        chessboard.black.pop_back();
                        break;
                    }
                }
                chessboard.white[0].x = moves[0][1];
                chessboard.white[0].y = moves[0][0];
            }


        }
        int k = 0;
        int n = 0;
        int b = 0;
        int r = 0;
        for (int i = 0; i < chessboard.white.size(); i++) {
            if (chessboard.white[i].name == "k") { k += 1; }
            if (chessboard.white[i].name == "n") { n += 1; }
            if (chessboard.white[i].name == "b") { b += 1; }
            if (chessboard.white[i].name == "r") { r += 1; }
        }
        for (int i = 0; i < chessboard.black.size(); i++) {
            if (chessboard.black[i].name == "K") { k += 1; }
            if (chessboard.black[i].name == "N") { n += 1; }
            if (chessboard.black[i].name == "B") { b += 1; }
            if (chessboard.black[i].name == "R") { r += 1; }

        }
        if (k == 2 && n > 2 && b > 2 && r > 2) { t = 0; }
        for (int i = 0; i < chessboard.white.size(); i++) {
            moves = chessboard.move(chessboard.white[i]);
            for (int j = 0; j < moves.size(); j++) {
                if (chessboard.board[moves[j][0]][moves[j][1]].name == "K") { t = 1; break; }
            }
        }
        for (int i = 0; i < chessboard.black.size(); i++) {
            moves = chessboard.move(chessboard.black[i]);
            for (int j = 0; j < moves.size(); j++) {
                if (chessboard.board[moves[j][0]][moves[j][1]].name == "k") { t = 1; break; }
            }
        }
    }
    chessboard.printBoard();
    ChessBoard cb;
    int first = 0;
    int second = 0;
    int third = 0;
    std::vector<std::vector<int>> winmoves1;
    std::vector<std::vector<int>> winmoves2;
    std::vector<std::vector<int>> winmoves3;
    for (int i = 0; i < chessboard.white.size(); i++) {
        moves = chessboard.move(chessboard.white[i]);
        for (int j = 0; j < moves.size(); j++) {
            int score = 0;
            cb.make();
            cb.white.clear();
            cb.board.clear();
            cb.board = chessboard.board;
            cb.white = chessboard.white;
            if (cb.board[moves[j][0]][moves[j][1]].name == "P") { score += 1; }
            if (cb.board[moves[j][0]][moves[j][1]].name == "B") { score += 3; }
            if (cb.board[moves[j][0]][moves[j][1]].name == "N") { score += 3; }
            if (cb.board[moves[j][0]][moves[j][1]].name == "R") { score += 5; }
            cb.board[moves[j][0]][moves[j][1]] = cb.white[i];
            cb.board[cb.white[i].y][cb.white[i].x] = Piece();
            cb.white[i].x = moves[j][1];
            cb.white[i].y = moves[j][0];
            for (int k = 0; k < cb.white.size(); k++) {
                std::vector<std::vector<int>> moves1;
                moves1 = chessboard.move(cb.white[k]);
                for (int l = 0; l < moves1.size(); l++) {
                    int score1 = score;
                    ChessBoard cb1;
                    cb1.make();
                    cb1.white.clear();
                    cb1.board.clear();
                    cb1.board = cb.board;
                    cb1.white = cb.white;
                    if (cb1.board[moves1[l][0]][moves1[l][1]].name == "P") { score1 += 1; }
                    if (cb1.board[moves1[l][0]][moves1[l][1]].name == "B") { score1 += 3; }
                    if (cb1.board[moves1[l][0]][moves1[l][1]].name == "N") { score1 += 3; }
                    if (cb1.board[moves1[l][0]][moves1[l][1]].name == "R") { score1 += 5; }
                    if (cb1.board[moves1[l][0]][moves1[l][1]].name == "K") {
                        score1 += 1;
                        if (third < score1) {
                            winmoves3.clear();
                            third = score1;
                            winmoves3 = { {chessboard.white[i].y, chessboard.white[i].x}, moves[j], {cb1.white[k].y, cb1.white[k].x}, moves1[l] };
                        }
                        if (second < third) {
                            int repl;
                            std::vector<std::vector<int>> replvec;
                            replvec.clear();
                            repl = third;
                            third = second;
                            second = repl;
                            replvec = winmoves2;
                            winmoves2.clear();
                            winmoves2 = winmoves3;
                            winmoves3.clear();
                            winmoves3 = replvec;
                        }
                        if (first < second) {
                            int repl;
                            std::vector<std::vector<int>> replvec;
                            replvec.clear();
                            repl = second;
                            second = first;
                            first = repl;
                            replvec = winmoves1;
                            winmoves1.clear();
                            winmoves1 = winmoves2;
                            winmoves2.clear();
                            winmoves2 = replvec;
                        }


                        continue;

                    }
                    cb1.board[moves1[l][0]][moves1[l][1]] = cb1.white[k];
                    cb1.board[cb1.white[k].y][cb1.white[k].x] = Piece();
                    cb1.white[k].x = moves1[l][1];
                    cb1.white[k].y = moves1[l][0];
                    for (int m = 0; m < cb1.white.size(); m++) {
                        std::vector<std::vector<int>> moves2;
                        moves2 = chessboard.move(cb1.white[m]);
                        for (int n = 0; n < moves2.size(); n++) {
                            ChessBoard cb2;
                            cb2.make();
                            cb2.white.clear();
                            cb2.board.clear();
                            cb2.board = cb1.board;
                            cb2.white = cb1.white;
                            int score2 = score1;
                            if (cb2.board[moves2[n][0]][moves2[n][1]].name == "P") { score2 += 1; }
                            if (cb2.board[moves2[n][0]][moves2[n][1]].name == "B") { score2 += 3; }
                            if (cb2.board[moves2[n][0]][moves2[n][1]].name == "N") { score2 += 3; }
                            if (cb2.board[moves2[n][0]][moves2[n][1]].name == "R") { score2 += 5; }
                            if (cb2.board[moves2[n][0]][moves2[n][1]].name == "K") {
                                score2 += 1;
                                if (third < score2) {
                                    winmoves3.clear();
                                    third = score2;
                                    winmoves3 = { {chessboard.white[i].y, chessboard.white[i].x}, moves[j], {cb.white[k].y, cb.white[k].x}, moves1[l], {cb1.white[m].y, cb1.white[m].x} , moves2[n] };
                                }
                                if (second < third) {
                                    int repl;
                                    std::vector<std::vector<int>> replvec;
                                    replvec.clear();
                                    repl = third;
                                    third = second;
                                    second = repl;
                                    replvec = winmoves2;
                                    winmoves2.clear();
                                    winmoves2 = winmoves3;
                                    winmoves3.clear();
                                    winmoves3 = replvec;
                                }
                                if (first < second) {
                                    int repl;
                                    std::vector<std::vector<int>> replvec;
                                    replvec.clear();
                                    repl = second;
                                    second = first;
                                    first = repl;
                                    replvec = winmoves1;
                                    winmoves1.clear();
                                    winmoves1 = winmoves2;
                                    winmoves2.clear();
                                    winmoves2 = replvec;
                                }
                                continue;

                            }
                            cb2.board[moves2[n][0]][moves2[n][1]] = cb2.white[m];
                            cb2.board[cb2.white[m].y][cb2.white[m].x] = Piece();
                            cb2.white[m].x = moves2[n][1];
                            cb2.white[m].y = moves2[n][0];
                            std::vector<std::vector<int>> moves3;
                            moves3 = chessboard.move(cb2.white[m]);
                            for (int p = 0; p < moves3.size(); p++) {
                                if (cb2.board[moves3[p][0]][moves3[p][1]].name == "K") { score2 += 1; break; }

                            }

                            if (third < score2) {
                                winmoves3.clear();
                                third = score2;
                                winmoves3 = { {chessboard.white[i].y, chessboard.white[i].x}, moves[j], {cb.white[k].y, cb.white[k].x}, moves1[l], {cb1.white[m].y, cb1.white[m].x} , moves2[n] };
                            }
                            if (second < third) {
                                int repl;
                                std::vector<std::vector<int>> replvec;
                                replvec.clear();
                                repl = third;
                                third = second;
                                second = repl;
                                replvec = winmoves2;
                                winmoves2.clear();
                                winmoves2 = winmoves3;
                                winmoves3.clear();
                                winmoves3 = replvec;
                            }
                            if (first < second) {
                                int repl;
                                std::vector<std::vector<int>> replvec;
                                replvec.clear();
                                repl = second;
                                second = first;
                                first = repl;
                                replvec = winmoves1;
                                winmoves1.clear();
                                winmoves1 = winmoves2;
                                winmoves2.clear();
                                winmoves2 = replvec;
                            }

                        }
                    }
                }
            }
        }

    }
    std::cout << "1st" << "\n";
    std::vector<char> cords = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    for (int i = 0; i < winmoves1.size(); i += 2) {
        std::cout << cords[winmoves1[i][1]] << ' ' << winmoves1[i][0] + 1;
        std::cout << " -----> ";
        std::cout << cords[winmoves1[i + 1][1]] << ' ' << winmoves1[i + 1][0] + 1 << '\n';
    }
    std::cout << "2nd" << "\n";
    for (int i = 0; i < winmoves2.size(); i += 2) {
        std::cout << cords[winmoves2[i][1]] << ' ' << winmoves2[i][0] + 1;
        std::cout << " -----> ";
        std::cout << cords[winmoves2[i + 1][1]] << ' ' << winmoves2[i + 1][0] + 1 << '\n';
    }
    std::cout << "3rd" << "\n";
    for (int i = 0; i < winmoves3.size(); i += 2) {
        std::cout << cords[winmoves3[i][1]] << ' ' << winmoves3[i][0] + 1;
        std::cout << " -----> ";
        std::cout << cords[winmoves3[i + 1][1]] << ' ' << winmoves3[i + 1][0] + 1 << '\n';
    }
    return 0;
}


















































