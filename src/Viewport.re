type t;

[@bs.deriving accessors]
type scale =
  | ScaleValue(float)
  | ScalePageActual
  | ScalePageHeight
  | ScalePageWidth
  | ScalePageFit
  | ScaleAuto;

[@bs.get] external width: t => float = "";

[@bs.get] external height: t => float = "";

[@bs.get] external scale: t => float = "";

[@bs.get] external transform: t => Js.Array.t(float) = "";

[@bs.send.pipe: t]
external convertToPdfPoint: (float, float) => Js.Array.t(float) = "";

[@bs.send.pipe: t]
external convertToViewportPoint: (float, float) => Js.Array.t(float) = "";

[@bs.send.pipe: t] external clone: {. "dontFlip": bool} => t = "";

let clone = (~dontFlip=false, viewport) =>
  clone({"dontFlip": dontFlip}, viewport);