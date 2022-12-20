#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "../graphics/graphics.h"
const int sizeOfCell = 40, shiftX = (800 - (sizeOfCell * 8)) / 2, shiftY = 120,
          countViruses = 11;
enum Side { first, second };
enum Position { HORIZONTAL, VERTICAL };
enum Color { BLUE, RED, YELLOW, NONEC };

enum Direction { NONE, DOWN, LEFT, RIGHT, MOVEfirst, MOVEsecond };
enum Rotation { RNONE, RRIGHT, RLEFT };

class Cell {
 public:
  virtual ~Cell() = default;
  virtual void Render(int x, int y) = 0;

  void OnVisit(std::function<void()> on_visit) { this->on_visit = on_visit; }

  void Visit() {
    if (on_visit) {
      on_visit();
    }
  }
  Color col = Color::NONEC;
  bool operator==(Color c) {
    return (col == Color::BLUE && c == Color::BLUE ||
            col == Color::YELLOW && c == Color::YELLOW ||
            col == Color::RED && c == Color::RED);
  }
  bool poisoned = 0;

 private:
  std::function<void()> on_visit;

 protected:
  int frame = 0;
};

class EmptyCell : public Cell {
 public:
  void Render(int x, int y) override {
    // SDL_SetRenderDrawColor(render::GetRenderer(), 255, 0, 255, 255);
    // SDL_RenderDrawRect(
    //     render::GetRenderer(),
    //     render::MakeRect(x * sizeOfCell + shiftX, y * sizeOfCell + shiftY,
    //                      sizeOfCell, sizeOfCell));
  }
};

class PillCell : public Cell {
 public:
  void Render(int x, int y) override {
    render::LoadResource("resources/images/pill_left_red.png");
    render::LoadResource("resources/images/pill_left_yellow.png");
    render::LoadResource("resources/images/pill_left_blue.png");

    render::LoadResource("resources/images/pill_right_red.png");
    render::LoadResource("resources/images/pill_right_yellow.png");
    render::LoadResource("resources/images/pill_right_blue.png");

    if (side == Side::first) {
      if (col == RED)
        render::DrawImage("pill_left_red.png", x * sizeOfCell + shiftX,
                          y * sizeOfCell + shiftY, sizeOfCell, sizeOfCell);
      else if (col == YELLOW)
        render::DrawImage("pill_left_yellow.png", x * sizeOfCell + shiftX,
                          y * sizeOfCell + shiftY, sizeOfCell, sizeOfCell);
      else
        render::DrawImage("pill_left_blue.png", x * sizeOfCell + shiftX,
                          y * sizeOfCell + shiftY, sizeOfCell, sizeOfCell);
    } else {
      if (col == RED)
        render::DrawImage("pill_right_red.png", x * sizeOfCell + shiftX,
                          y * sizeOfCell + shiftY, sizeOfCell, sizeOfCell);
      else if (col == YELLOW)
        render::DrawImage("pill_right_yellow.png", x * sizeOfCell + shiftX,
                          y * sizeOfCell + shiftY, sizeOfCell, sizeOfCell);
      else
        render::DrawImage("pill_right_blue.png", x * sizeOfCell + shiftX,
                          y * sizeOfCell + shiftY, sizeOfCell, sizeOfCell);
    }
  }
  Side side;

 private:
};

class VirusCell : public Cell {
 public:
  void Render(int x, int y) {
    if (this->col == Color::BLUE)
      render::DrawImageFromAtlas("blue_virus", "dancing", frame / 20 % 3,
                                 x * sizeOfCell + shiftX,
                                 y * sizeOfCell + shiftY);
    else if (col == Color::RED)
      render::DrawImageFromAtlas("red_virus", "dancing", frame / 20 % 3,
                                 x * sizeOfCell + shiftX,
                                 y * sizeOfCell + shiftY);
    else if (col == Color::YELLOW)
      render::DrawImageFromAtlas("yellow_virus", "dancing", frame / 20 % 3,
                                 x * sizeOfCell + shiftX,
                                 y * sizeOfCell + shiftY);
    ++frame;
  }
};

struct Coords {
  int x, y;

  bool operator==(const Coords& o) const { return x == o.x && y == o.y; }
};

class Pill {
 public:
  explicit Pill(const Coords& pos1) {
    srand(time(NULL));
    posFirst = pos1;
    posSecond = {pos1.x + 1, pos1.y};
    direction = NONE;
    first.side = Side::first;
    second.side = Side::second;
    first.col = static_cast<Color>(rand() % 3);   // (rand() % 3);   //% 3);
    second.col = static_cast<Color>(rand() % 3);  // rand() % 3);  // % 3);
  }

  std::pair<Coords, Coords> GetPos() {
    return std::make_pair(posFirst, posSecond);
  }
  PillCell* Getsecond() { return &second; }
  PillCell* Getfirst() { return &first; }

  void SetPos(Coords pos1, Coords pos2) {
    posFirst = pos1;
    posSecond = pos2;
  }
  void SetCol() {
    first.col = static_cast<Color>(rand() % 3);   //% 3);
    second.col = static_cast<Color>(rand() % 3);  //% 3);
  }
  void SetDirection(Direction dir) {
    // if (direction != NONE && dir == NONE) return;
    direction = dir;
  }
  Direction GetDirection() {
    // if (direction != NONE && dir == NONE) return;
    return direction;
  }
  void SetRotation(Rotation rot) {
    if (rotation != RNONE && rot == RNONE) return;
    rotation = rot;
  }

  void UpdateState() {
    UpdateDirection();
    UpdatePosition();
  }

  void UpdateDirection() {
    if (pos == Position::HORIZONTAL && rotation != Rotation::RNONE) {
      if (posFirst.x < posSecond.x && rotation == Rotation::RLEFT) {
        posSecond = {posSecond.x - 1, posSecond.y - 1};
      } else if (posFirst.x > posSecond.x && rotation == Rotation::RRIGHT) {
        posFirst = {posFirst.x - 1, posFirst.y};
        posSecond = {posSecond.x, posSecond.y - 1};
      } else if (posFirst.x < posSecond.x) {
        posFirst = {posFirst.x, posFirst.y - 1};
        posSecond = {posSecond.x - 1, posSecond.y};
      } else {
        posFirst = {posFirst.x - 1, posFirst.y - 1};
      }
      rotation = Rotation::RNONE;

      pos = Position::VERTICAL;
    } else if (pos == Position::VERTICAL && rotation != Rotation::RNONE) {
      if (posFirst.y < posSecond.y && rotation == Rotation::RLEFT) {
        posFirst = {posFirst.x, posFirst.y + 1};
        posSecond = {posSecond.x + 1, posSecond.y};
      } else if (posFirst.y > posSecond.y && rotation == Rotation::RRIGHT) {
        posSecond = {posSecond.x + 1, posSecond.y + 1};
      } else if (posFirst.y < posSecond.y) {
        posFirst = {posFirst.x + 1, posFirst.y + 1};
      } else {
        posFirst = {posFirst.x + 1, posFirst.y};
        posSecond = {posSecond.x, posSecond.y + 1};
      }
      rotation = Rotation::RNONE;

      pos = Position::HORIZONTAL;
    }
  }
  void UpdatePosition() {
    switch (direction) {
      case NONE:
        return;
      case DOWN:
        posFirst.y++;
        posSecond.y++;
        break;
      case RIGHT:
        direction = DOWN;
        if (posFirst.y == 0 && pos == HORIZONTAL) break;
        posFirst.x++;
        posSecond.x++;
        break;
      case LEFT:
        direction = DOWN;
        if (posFirst.y == 0 && pos == HORIZONTAL) break;
        posFirst.x--;
        posSecond.x--;
        break;
    }
  }
  void Render() {
    first.Render(posFirst.x, posFirst.y);
    second.Render(posSecond.x, posSecond.y);
  }
  Position GetOrientation() { return pos; }

 private:
  Coords posFirst;
  Coords posSecond;
  Direction direction;
  // Direction tmpDir;
  PillCell first;
  PillCell second;
  Position pos = Position::HORIZONTAL;
  Rotation rotation = Rotation::RNONE;
};

class GameField {
 public:
  GameField(int w = 8, int h = 16) {
    fields.resize(w);
    for (auto& column : fields) {
      column.resize(h);
      for (auto& cell : column) {
        cell = std::make_unique<EmptyCell>();
      }
    }
  }

  int GetWidth() const { return fields.size(); }
  int GetHeight() const { return fields[0].size(); }

  void Render() {
    // Render background
    for (int x = 0; x < GetWidth(); ++x) {
      for (int y = 0; y < GetHeight(); ++y) {
        fields[x][y]->Render(x, y);
      }
    }
  }

  Cell* GetCell(int x, int y) const {
    if (x < 0 || x >= fields.size()) return nullptr;
    if (y < 0 || y >= fields[x].size()) return nullptr;
    return fields[x][y].get();
  }

  Cell* SetCell(int x, int y, Cell* cell) {
    fields[x][y].reset(cell);
    return fields[x][y].get();
  }

 private:
  std::vector<std::vector<std::unique_ptr<Cell>>> fields;
};