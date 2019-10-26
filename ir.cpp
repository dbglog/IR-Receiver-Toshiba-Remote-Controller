#include "pxt.h"
#include <map>
#include <vector>
#include "ReceiverIR.h"
using namespace pxt;
typedef vector<Action> vA;

enum class Pins
{
  P0 = 3,
  P1 = 2,
  P2 = 1,
  P3 = 4,
  P4 = 5,
  P5 = 17,
  P6 = 12,
  P7 = 11,
  P8 = 18,
  P9 = 10,
  P10 = 6,
  P11 = 26,
  P12 = 20,
  P13 = 23,
  P14 = 22,
  P15 = 21,
  P16 = 16,
  P19 = 0,
  P20 = 30
};

enum class RemoteButton
{
  //Toshiba TV Remote controler
  B1 = 0x01,
  B2 = 0x02,
  B3 = 0x03,
  B4 = 0x04,
  B5 = 0x05,
  B6 = 0x06,
  B7 = 0x07,
  B8 = 0x08,
  B9 = 0x09,
  B10 = 0x0A,
  B11 = 0x0B,
  B12 = 0x0C,
  MUTE = 0x10,
  POWER = 0x12,
  VOLUP = 0x1A,
  CHUP = 0x1B,
  VOLDOWN = 0x1E,
  CHDOWN = 0x1F,
  BACK = 0x3B,
  END = 0x3C,
  SELECT = 0x3D,
  DIR_UP = 0x3E,
  DIR_DOWN = 0x3F,
  DIR_RIGHT = 0x5B,
  DIR_LEFT = 0x5F,
  COL_BLUE = 0x73,
  COL_RED = 0x74,
  COL_GREEN = 0x75,
  COL_YELLOW = 0x76,

  /*
  Power = 0x0,
  Up = 0x5,
  Left = 0x8,
  Right = 0xA,
  Down = 0xD,
  OK = 0x9,
  Plus = 0x4,
  Minus = 0xC,
  Back = 0x6
  */
};

//% color=50 weight=80
//% icon="\uf1eb"
namespace IR
{
map<RemoteButton, vA> actions;
map<RemoteButton, uint32_t> lastact;
Timer tsb;
uint8_t buf[32];
uint32_t now;
ReceiverIR *rx;
RemoteIR::Format fmt = RemoteIR::UNKNOWN;

void cA(vA runner)
{
  for (int i = 0; i < runner.size(); i++)
  {
    runAction0(runner[i]);
  }
}

void onReceivable()
{
  int x = rx->getData(&fmt, buf, 32 * 8);
  if (actions.find((RemoteButton)buf[2]) == actions.end())
    return;
  now = tsb.read_ms();
  if (now - lastact[(RemoteButton)buf[2]] < 100)
    return;
  lastact[(RemoteButton)buf[2]] = now;
  cA(actions[(RemoteButton)buf[2]]);
}

void monitorIR()
{
  while (1)
  {
    while (rx->getState() != ReceiverIR::Received)
    {
      uBit.sleep(50);
    }
    onReceivable();
  }
}

//%
void init(Pins pin)
{
  rx = new ReceiverIR((PinName)pin);
  tsb.start(); //interrupt timer for debounce
  create_fiber(monitorIR);
}

//%
void onPressEvent(RemoteButton btn, Action body)
{
  //if(actions.find(btn) == actions.end()) actions[btn] = new vector();
  actions[btn].push_back(body);
}
} // namespace IR
