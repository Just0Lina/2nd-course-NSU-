#include <algorithm>
#include <iostream>

#include "app/baseapp.h"
#include "pill/pill.h"
#define here std::cout << "HERE1" << std::endl

enum State { MENU, GAME, fallingPill };

class GameApp : public app::GameApp {
 public:
  GameApp(int w, int h)
      : app::GameApp(w, h), pill({game_field.GetWidth() / 2 - 1, 0}) {}

 private:
  void AddViruses() {  // std::vector<std::pair<int, int>> coord;

    std::vector<int> xPos;
    std::vector<int> yPos;
    for (int i = 0; i < countViruses; ++i) {
      int x = rand() % game_field.GetWidth();
      int y =
          rand() % (game_field.GetHeight() / 2) + (game_field.GetHeight() / 2);

      while (find(xPos.begin(), xPos.end(), x) != xPos.end() &&
             find(yPos.begin(), yPos.end(), y) != yPos.end()) {
        x = rand() % game_field.GetWidth();
        y = rand() % (game_field.GetHeight() / 2) +
            (game_field.GetHeight() / 2);
      }
      xPos.push_back(x);
      yPos.push_back(y);
      int col = rand() % 3;  //% 3;
      auto* viruses = new VirusCell;
      viruses->col = static_cast<Color>(col);
      viruses->poisoned = 1;

      viruses->OnVisit([this, x, y]() mutable {
        NewPill(pill.GetPos().first.x, pill.GetPos().first.y - 1,
                pill.GetPos().second.x, pill.GetPos().second.y - 1);

        UpdateState();
      });
      game_field.SetCell(x, y, viruses);
    }
  }

  void Initialize() override {
    render::LoadResource("resources/images/background.png", "background");

    render::LoadResource("resources/images/backdrop.png", "backdrop");

    render::LoadResource("resources/images/black.jpeg", "black");
    render::LoadResource("resources/images/menu.png", "menu");

    auto menuAtlas = render::Atlas::Create("resources/images/menu.png", "menu");

    menuAtlas.AddAnimationLine("pause")
        .SetFramesCount(4, false)
        .SetFrameHeight(800)
        .SetFrameWidth(800);
    render::BakeAtlas(menuAtlas);

    auto blueVirusAtlas =
        render::Atlas::Create("resources/images/blue_virus.png", "blue_virus");

    blueVirusAtlas.AddAnimationLine("dancing")
        .SetFramesCount(3, false)
        .SetFrameHeight(40)
        .SetFrameWidth(40);
    render::BakeAtlas(blueVirusAtlas);
    auto redVirusAtlas =
        render::Atlas::Create("resources/images/red_virus.png", "red_virus");

    redVirusAtlas.AddAnimationLine("dancing")
        .SetFramesCount(3, false)
        .SetFrameHeight(40)
        .SetFrameWidth(40);
    render::BakeAtlas(redVirusAtlas);

    auto yellowVirusAtlas = render::Atlas::Create(
        "resources/images/yellow_virus.png", "yellow_virus");

    yellowVirusAtlas.AddAnimationLine("dancing")
        .SetFramesCount(3, false)
        .SetFrameHeight(40)
        .SetFrameWidth(40);
    render::BakeAtlas(yellowVirusAtlas);
    AddViruses();
  }

  void ProcessInput(const Uint8* keyboard, const MouseState& mouse) override {
    auto pillPos = pill.GetPos();
    if (keyboard[SDL_SCANCODE_SPACE]) {
      if (pill.GetDirection() == NONE)
        pill.SetDirection(DOWN);
      else
        pill.SetDirection(NONE);
    }

    if (keyboard[SDL_SCANCODE_RIGHT]) {
      if (game_field.GetCell(pillPos.first.x + 1, pillPos.first.y)->col ==
          NONEC)
        pill.SetDirection(RIGHT);
    } else if (keyboard[SDL_SCANCODE_LEFT]) {
      if (game_field.GetCell(pillPos.first.x - 1, pillPos.first.y)->col ==
          NONEC)
        pill.SetDirection(LEFT);
    } else if (keyboard[SDL_SCANCODE_DOWN]) {
      pill.SetDirection(DOWN);
    } else if (keyboard[SDL_SCANCODE_J]) {
      pill.SetRotation(RLEFT);
    } else if (keyboard[SDL_SCANCODE_K]) {
      pill.SetRotation(RRIGHT);
    }
    if (keyboard[SDL_SCANCODE_RETURN]) {
      if (st == MENU) st = GAME;
      pill.SetDirection(DOWN);
    }
  }

  void CornerCases() {
    auto pillPos = pill.GetPos();
    if (pillPos.first.x < 0) {
      ++pillPos.first.x;
      ++pillPos.second.x;
    }
    if (pillPos.second.x >= game_field.GetWidth()) {
      --pillPos.first.x;
      --pillPos.second.x;
    }

    if (pillPos.second.y >= game_field.GetHeight()) {
      --pillPos.first.y;
      --pillPos.second.y;
    }

    pill.SetPos(pillPos.first, pillPos.second);
    if (pillPos.second.y == game_field.GetHeight() - 1) {
      NewPill(pillPos.first.x, pillPos.first.y, pillPos.second.x,
              pillPos.second.y);
    }
  }

  void Render() override {
    // render::DrawImage("white", 1, 1, 800, 800);
    if (st == GAME || st == fallingPill) {
      render::DrawImage("background", 1, 1, 800, 800);
      render::DrawImage("black", shiftX, shiftY + 40, 320, 600);
      render::DrawImage("backdrop", 180, 0, 425, 800);
      game_field.Render();
      pill.Render();
    } else {
      render::DrawImageFromAtlas("menu", "pause", millis_ / 150 % 4, 0, 0);
      // render    }
    }
  }
  void Update(Uint32 millis) override {
    const int kQuant = 400;
    millis_ += millis;
    if (millis_ < kQuant) {
      return;
    }

    millis_ -= kQuant;
    // // here;
    if (st == fallingPill) {
      // std::cout << "HERE" << std::endl;
      bool flag = 0;
      std::vector<Coords> tmpFall;
      for (auto& v : fallingPills) {
        if (v.y + 1 < game_field.GetHeight() &&
            game_field.GetCell(v.x, v.y + 1)->col == NONEC) {
          // std::cout << v.x << " " << v.y << std::endl;

          auto* field = new PillCell;
          field->col = game_field.GetCell(v.x, v.y)->col;

          field->OnVisit([this]() mutable {
            NewPill(pill.GetPos().first.x, pill.GetPos().first.y - 1,
                    pill.GetPos().second.x, pill.GetPos().second.y - 1);
            UpdateState();
          });
          if (v.y + 2 < game_field.GetHeight() &&
              !game_field.GetCell(v.x, v.y + 2)->poisoned)
            tmpFall.push_back({v.x, v.y + 1});
          game_field.SetCell(v.x, v.y + 1, field);

          auto* t = new EmptyCell;

          game_field.SetCell(v.x, v.y, t);

          flag = 1;
        }
      }
      fallingPills = tmpFall;
      UpdateState();
      if (!flag) {
        st = GAME;
        pill.SetDirection(DOWN);
      }
    } else {
      pill.UpdateState();
      SetPillVisited();
      CornerCases();
    }
  }

  void SetPillVisited() {
    if (Cell* cell =
            game_field.GetCell(pill.GetPos().first.x, pill.GetPos().first.y))
      cell->Visit();
    if (Cell* cell =
            game_field.GetCell(pill.GetPos().second.x, pill.GetPos().second.y))
      cell->Visit();
  }

  bool UpdateState() {
    bool flag = 1;
    int countX = 0, countY = 0;
    Color startCx = game_field.GetCell(0, 0)->col,
          startCy = game_field.GetCell(0, 0)->col;
    for (int x = 0; x < game_field.GetWidth(); ++x) {
      startCy = game_field.GetCell(x, 0)->col;
      countY = 0;
      for (int y = 0; y < game_field.GetHeight(); ++y) {
        if (game_field.GetCell(x, y)->col == startCy && startCy != NONEC) {
          ++countY;
        } else {
          if (countY > 2) {
            for (int i = y - 1; i >= y - countY; --i) {
              if (x > 0 && game_field.GetCell(x - 1, i)->col != NONEC &&
                  !game_field.GetCell(x - 1, i)->poisoned &&
                  i + 1 < game_field.GetHeight()) {
                fallingPills.push_back({x - 1, i});
              }
              if (x + 1 < game_field.GetWidth() &&
                  game_field.GetCell(x + 1, i)->col != NONEC &&
                  !game_field.GetCell(x + 1, i)->poisoned &&
                  i + 1 < game_field.GetHeight()) {
                fallingPills.push_back({x + 1, i});
              }
              auto* a = new EmptyCell;
              Coords tmp = {x, i};
              // fallingPills.erase(
              //     find(fallingPills.begin(), fallingPills.end(), tmp));
              game_field.SetCell(x, i, a);
            }
            st = fallingPill;
            pill.SetDirection(NONE);
          }
          countY = 1;
          startCy = game_field.GetCell(x, y)->col;
        }
      }
      if (countY > 2) {
        st = fallingPill;
        pill.SetDirection(NONE);
        for (int i = game_field.GetHeight() - 1;
             i >= game_field.GetHeight() - countY; --i) {
          if (x > 0 && game_field.GetCell(x - 1, i)->col != NONEC &&
              !game_field.GetCell(x - 1, i)->poisoned &&
              i + 1 < game_field.GetHeight() &&
              game_field.GetCell(x - 1, i + 1)->col == NONEC) {
            fallingPills.push_back({x - 1, i});
          }
          if (x + 1 < game_field.GetWidth() &&
              game_field.GetCell(x + 1, i)->col != NONEC &&
              !game_field.GetCell(x + 1, i)->poisoned &&
              i + 1 < game_field.GetHeight() &&
              game_field.GetCell(x + 1, i + 1)->col == NONEC) {
            fallingPills.push_back({x + 1, i});
          }
          auto* a = new EmptyCell;
          game_field.SetCell(x, i, a);
        }
      }
    }

    for (int y = 0; y < game_field.GetHeight(); ++y) {
      startCx = game_field.GetCell(0, y)->col;
      countX = 0;
      for (int x = 0; x < game_field.GetWidth(); ++x) {
        if (game_field.GetCell(x, y)->col == startCx && startCx != NONEC) {
          ++countX;
        } else {
          if (countX > 2) {
            for (int i = x - 1; i >= x - countX; --i) {
              if (y > 0 && game_field.GetCell(i, y - 1)->col != NONEC &&
                  !game_field.GetCell(i, y - 1)->poisoned) {
                fallingPills.push_back({i, y - 1});
              }
              if (y + 1 < game_field.GetHeight() &&
                  game_field.GetCell(i, y + 1)->col != NONEC &&
                  !game_field.GetCell(i, y + 1)->poisoned &&
                  y + 2 < game_field.GetHeight() &&
                  game_field.GetCell(i, y + 2)->col == NONEC) {
                fallingPills.push_back({i, y + 1});
              }
              auto* a = new EmptyCell;
              game_field.SetCell(i, y, a);
            }
          }
          countX = 1;
          startCx = game_field.GetCell(x, y)->col;
        }
      }
      if (countX > 2) {
        for (int i = game_field.GetWidth() - 1;
             i >= game_field.GetWidth() - countX; --i) {
          auto* a = new EmptyCell;
          game_field.SetCell(i, y, a);
        }
      }
    }

    return flag;
  }
  //
  void NewPill(int x1, int y1, int x2, int y2) {
    if (y1 - 1 < 0) {
      GameOver();
      return;
    }
    PillCell* tmpPill = new PillCell;
    tmpPill->side = Side::first;
    tmpPill->col = pill.Getfirst()->col;

    PillCell* tmpPill2 = new PillCell;
    tmpPill2->side = Side::second;
    tmpPill2->col = pill.Getsecond()->col;

    Pill pilll = pill;
    tmpPill->OnVisit([this, pilll]() mutable {
      // Pill tmp = pill;
      // std::cout << "1st: " << pilll.GetPos().first.x << " "
      //           << pilll.GetPos().first.y - 1 << std::endl;
      NewPill(pilll.GetPos().first.x, pilll.GetPos().first.y - 2,
              pilll.GetPos().second.x, pilll.GetPos().second.y - 2);
      UpdateState();
    });

    tmpPill2->OnVisit([this, pilll]() mutable {
      // Pill tmp = pill;
      // std::cout << "2nd: " << pilll.GetPos().first.x << " "
      //           << pilll.GetPos().first.y - 1 << std::endl;
      NewPill(pilll.GetPos().first.x, pilll.GetPos().first.y - 2,
              pilll.GetPos().second.x, pilll.GetPos().second.y - 2);
      UpdateState();
    });

    pill.SetPos({game_field.GetWidth() / 2 - 1, 0},
                {game_field.GetWidth() / 2, 0});
    pill.SetCol();
    game_field.SetCell(x1, y1, tmpPill);
    game_field.SetCell(x2, y2, tmpPill2);
  }

  GameField game_field;
  Pill pill;
  std::vector<Coords> fallingPills;
  std::vector<VirusCell> viruses;
  Uint32 millis_ = 0;
  State st = MENU;
};

#undef main
int main() {
  try {
    GameApp(800, 800).Run();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}