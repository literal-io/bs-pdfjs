open InternalUtils;

module Destination = {
  type t = (string, array(option(float)));
  /** Destination array is polymorphic, manually coorce to int */
  external toNullableFloat: {.. "name": string} => Js.nullable(float) =
    "%identity";
  /**
   * Parsing logic depends on viewer state e.g. height, scale, so we
   * convert into a reasonable state, but leave unparsed.
   **/
  let decode = (json): t => {
    let name = json[1]##name;
    let values =
      json
      |> Js.Array.sliceFrom(1)
      |> Js.Array.map(value => value |> toNullableFloat |> Js.Nullable.to_opt);
    (name, values);
  };
  let name = ((name, _values): t) => name;
  let idx = (idx, (_name, values): t) => values[idx - 1];
};

module Viewer = {
  type t = {
    .
    [@bs.set] "currentPageNumber": int,
    [@bs.set] "pagesRotation": int,
    "scrollPageIntoView":
      {
        .
        "pageNumber": int,
        "destArray": {.},
      } =>
      unit,
  };
  let make =
      (
        ~onGetCurrentPageNumber,
        ~onGetRotation,
        ~onSetRotation,
        ~onSetCurrentPageNumber,
        ~onScrollPageIntoView,
        (),
      ) => {
    let _make: (unit => int, int => bool, unit => int, int => bool, 'a) => t = [%raw
      {|
      function (
        onGetCurrentPageNumber,
        onSetCurrentPageNumber,
        onGetRotation,
        onSetRotation,
        onScrollPageIntoView
      ) {
        return {
          get currentPageNumber() { return onGetCurrentPageNumber(); },
          set currentPageNumber(value) { return onSetCurrentPageNumber(value); },
          get pagesRotation() { return onGetRotation(); },
          set pagesRotation(value) { return onSetRotation(value); },
          scrollPageIntoView: onScrollPageIntoView
        };
      }
    |}
    ];
    _make(
      onGetCurrentPageNumber,
      onSetCurrentPageNumber,
      onGetRotation,
      onSetRotation,
      ev =>
      onScrollPageIntoView(
        ~pageNumber=ev##pageNumber,
        ~destination=Destination.decode(ev##destArray),
        (),
      )
    );
  };
};

/**
 * Internal LinkService bindings
 *
 * TODO: is pdfHistory necessary?
 * */
module PdfLinkService = {
  type t;
  [@bs.new] [@bs.module "pdfjs-dist/lib/web/pdf_link_service"]
  external make: unit => t = "PDFLinkService";
  [@bs.send.pipe: t] external setDocument: (Document.t, string) => unit = "";
  [@bs.send.pipe: t] external setViewer: Viewer.t => unit = "";
};

type t = PdfLinkService.t;

let make = (~viewer, ~pdfDocument, ~baseUrl, ()): t =>
  PdfLinkService.(
    make() *> setDocument(pdfDocument, baseUrl) *> setViewer(viewer)
  );