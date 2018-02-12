type t;

[@bs.deriving accessors]
type scale =
  | ScaleValue(float)
  | ScalePageActual
  | ScalePageHeight
  | ScalePageWidth
  | ScalePageFit
  | ScaleAuto;

[@bs.get] external width : t => float = "";

[@bs.get] external height : t => float = "";

[@bs.get] external scale : t => float = "";

[@bs.send.pipe : t]
external convertToPdfPoint : (float, float) => Js.Array.t(float) = "";

[@bs.send.pipe : t]
external convertToViewportPoint : (float, float) => Js.Array.t(float) = "";

[@bs.send.pipe : t] external clone : {. "dontFlip": Js.boolean} => t = "";

let clone = (~dontFlip=false, viewport) =>
  clone({"dontFlip": Js.Boolean.to_js_boolean(dontFlip)}, viewport);