type t;

type textContentStream;

module TextItem = {
  type t;
  [@bs.get] external str: t => string = "";
};

module TextContent = {
  type t;
  [@bs.get] external textItems: t => array(TextItem.t) = "items";
};

module Annotation = {
  type t;
};

module Transform = {
  type t = array(float);
  let make = (t1, t2, t3, t4, t5, t6) => [|t1, t2, t3, t4, t5, t6|];
};

[@bs.get] external pageNumber: t => int = "";

[@bs.send] external getViewport: (t, float, float, bool) => Viewport.t = "";

let getViewport = (~scale, ~rotate, ~dontFlip=false, page) =>
  getViewport(page, scale, rotate, dontFlip);

[@bs.send]
external getAnnotations: t => Js.Promise.t(array(Annotation.t)) = "";

[@bs.send] external streamTextContent: t => textContentStream = "";

[@bs.send] external getTextContent: t => Js.Promise.t(TextContent.t) = "";

[@bs.send.pipe: t]
external getTextContentWithParams:
  {
    .
    "normalizeWhitespace": bool,
    "disableCombineTextItems": bool,
  } =>
  Js.Promise.t(TextContent.t) =
  "getTextContent";

let getTextContentWithParams =
    (~normalizeWhitespace=false, ~disableCombineTextItems=false, pdfPage) =>
  getTextContentWithParams(
    {
      "normalizeWhitespace": normalizeWhitespace,
      "disableCombineTextItems": disableCombineTextItems,
    },
    pdfPage,
  );

[@bs.send]
external render:
  (
    t,
    {
      .
      "canvasContext": Webapi.Canvas.Canvas2d.t,
      "viewport": Viewport.t,
      "transform": Js.undefined(array(float)),
    }
  ) =>
  RenderTask.t(unit) =
  "";

let render = (~canvasContext, ~viewport, ~transform, page) =>
  render(
    page,
    {
      "viewport": viewport,
      "canvasContext": canvasContext,
      "transform": Js.Undefined.from_opt(transform),
    },
  );