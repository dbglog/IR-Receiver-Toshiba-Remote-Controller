

/**
 * IR remote
 */
    //% color=50 weight=80
    //% icon="\uf1eb"
namespace IR {

  /**
  * initialization
  */
  //% blockId=ir_init
  //% blockGap=20 weight=90
  //% block="connect ir receiver to %pin"
  //% shim=IR::init
  export function init(pin: Pins): void {
    return
  }

  /**
  * button pushed.
  */
  //% blockId=ir_received_event
  //% blockGap=20 weight=70
  //% block="on |%btn| button pressed"
  //% shim=IR::onPressEvent
  export function onPressEvent(btn: RemoteButton, body:Action): void {
    return
  }

}
