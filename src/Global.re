type t;

[@bs.module "pdfjs-dist"] external inst : t = "PDFJS";

[@bs.set] external setWorkerSrc : (t, string) => unit = "workerSrc";

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
    "textDivs": Js.Array.t(Dom.element)
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
      inst
    ) =>
  renderTextLayer(
    {
      "viewport": viewport,
      "container": container,
      "textDivs": textDivs,
      "textContent": Js.Nullable.from_opt(textContent),
      "textContentStream": Js.Nullable.from_opt(textContentStream)
    },
    inst
  );