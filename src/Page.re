type t;

type textContentStream;

type textContent;

[@bs.get] external pageNumber : t => int = "";

[@bs.send] external getViewport : (t, float, float) => Viewport.t = "";

[@bs.send] external streamTextContent : t => textContentStream = "";

[@bs.send] external getTextContent : t => textContent = "";

[@bs.send]
external render :
  (
    t,
    {
      .
      "canvasContext": Webapi.Canvas.Canvas2d.t,
      "viewport": Viewport.t
    }
  ) =>
  RenderTask.t(unit) =
  "";

let render = (~canvasContext, ~viewport, page) =>
  render(page, {"viewport": viewport, "canvasContext": canvasContext});