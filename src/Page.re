type t;

type textContentStream;

module TextItem = {
  type t;
  [@bs.get] external str: t => string = "";
  [@bs.get] external transform: t => Js.Array.t(float) = "";
  [@bs.get] external fontName: t => string = "";
  [@bs.get] external width: t => float = "";
};

module Styles = {
  type t;
  [@bs.get] external ascent: t => float = "";
  [@bs.get] external descent: t => float = "";
  [@bs.get] external fontFamily: t => string = "";
};

module TextContent = {
  type t;
  [@bs.get] external textItems: t => array(TextItem.t) = "items";
  [@bs.get] external textStyles: t => Js.Dict.t(Styles.t) = "styles";
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

[@bs.deriving abstract]
type canvasAndContext('a, 'b) = {
  canvas: 'a,
  context: 'b,
};

[@bs.deriving abstract]
type canvasFactory('a, 'b) = {
  create: (int, int) => canvasAndContext('a, 'b),
  reset: (canvasAndContext('a, 'b), int, int) => unit,
  destroy: canvasAndContext('a, 'b) => unit,
};

[@bs.send]
external createCanvasAndContext:
  (canvasFactory('a, 'b), int, int) => canvasAndContext('a, 'b) =
  "create";

[@bs.send]
external render:
  (
    t,
    {
      .
      "canvasContext": 'b,
      "viewport": Viewport.t,
      "transform": Js.undefined(array(float)),
      "canvasFactory": Js.undefined(canvasFactory('a, 'b)),
    }
  ) =>
  RenderTask.t(unit) =
  "";

let render = (~canvasContext, ~viewport, ~transform, ~canvasFactory, page) =>
  render(
    page,
    {
      "viewport": viewport,
      "canvasContext": canvasContext,
      "transform": Js.Undefined.fromOption(transform),
      "canvasFactory": Js.Undefined.fromOption(canvasFactory),
    },
  );