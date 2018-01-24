type t;

type canvasSize = {
  width: float,
  height: float,
  styleWidth: float,
  styleHeight: float
};

[@bs.get] external width : t => float = "width";

[@bs.get] external height : t => float = "height";

[@bs.send.pipe : t]
external convertToPdfPoint : (float, float) => Js.Array.t(float) = "";

[@bs.send.pipe : t]
external convertToViewportPoint : (float, float) => Js.Array.t(float) = "";