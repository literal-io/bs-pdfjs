type t;

[@bs.module] external inst : t = "pdfjs-dist";

[@bs.set] [@bs.scope "GlobalWorkerOptions"]
external setWorkerSrc : (t, string) => unit = "workerSrc";

[@bs.send.pipe : t]
external getDocument :
  (
  [@bs.unwrap]
  [
    | `UrlSource(Document.Source.url)
    | `TypedArraySource(Document.Source.typedArray)
  ]
  ) =>
  Js.Promise.t(Document.t) =
  "";

let getDocument = (source, pdfjs) =>
  switch source {
  | Document.Source.Url(source) => getDocument(`UrlSource(source), pdfjs)
  | Document.Source.TypedArray(source) =>
    getDocument(`TypedArraySource(source), pdfjs)
  };

[@bs.send.pipe : t]
external renderTextLayer :
  {
    .
    "textContent": Js.Nullable.t(Page.TextContent.t),
    "textContentStream": Js.Nullable.t(Page.textContentStream),
    "viewport": Viewport.t,
    "container": Dom.element,
    "textDivs": Js.Array.t(Dom.element),
    "enhanceTextSelection": Js.Nullable.t(bool)
  } =>
  RenderTask.t(unit) =
  "";

let renderTextLayer =
    (
      ~viewport,
      ~container,
      ~textDivs,
      ~textContent=?,
      ~textContentStream=?,
      ~enhanceTextSelection=?,
      inst
    ) =>
  renderTextLayer(
    {
      "viewport": viewport,
      "container": container,
      "textDivs": textDivs,
      "textContent": Js.Nullable.from_opt(textContent),
      "textContentStream": Js.Nullable.from_opt(textContentStream),
      "enhanceTextSelection": Js.Nullable.from_opt(enhanceTextSelection)
    },
    inst
  );

[@bs.scope "AnnotationLayer"] [@bs.send.pipe : t]
external renderAnnotationLayer :
  {
    .
    "annotations": array(Page.Annotation.t),
    "viewport": Viewport.t,
    "div": Dom.element,
    "page": Page.t,
    "linkService": LinkService.t
  } =>
  unit =
  "render";

let renderAnnotationLayer =
    (~viewport, ~annotations, ~div, ~page, ~linkService, inst) =>
  renderAnnotationLayer(
    {
      "viewport": viewport,
      "annotations": annotations,
      "div": div,
      "page": page,
      "linkService": linkService
    },
    inst
  );