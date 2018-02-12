type t;

type textContentStream;

module TextItem = {
  type t;
  [@bs.get] external str : t => string = "";
};

module TextContent = {
  type t;
  [@bs.get] external textItems : t => array(TextItem.t) = "items";
};

module Annotation = {
  type t;
};

[@bs.get] external pageNumber : t => int = "";

[@bs.send]
external getViewport : (t, float, float, Js.boolean) => Viewport.t = "";

let getViewport = (~scale, ~rotate, ~dontFlip=false, page) =>
  getViewport(page, scale, rotate, Js.Boolean.to_js_boolean(dontFlip));

[@bs.send]
external getAnnotations : t => Js.Promise.t(array(Annotation.t)) = "";

[@bs.send] external streamTextContent : t => textContentStream = "";

[@bs.send] external getTextContent : t => Js.Promise.t(TextContent.t) = "";

[@bs.send.pipe : t]
external getTextContentWithParams :
  {
    .
    "normalizeWhitespace": Js.boolean,
    "disableCombineTextItems": Js.boolean
  } =>
  Js.Promise.t(TextContent.t) =
  "getTextContent";

let getTextContentWithParams =
    (~normalizeWhitespace=false, ~disableCombineTextItems=false, pdfPage) =>
  getTextContentWithParams(
    {
      "normalizeWhitespace": Js.Boolean.to_js_boolean(normalizeWhitespace),
      "disableCombineTextItems":
        Js.Boolean.to_js_boolean(disableCombineTextItems)
    },
    pdfPage
  );

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