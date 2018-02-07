open InternalUtils;

module Destination = {
  type t;
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
        "destArray": Destination.t
      } =>
      unit
  };
  let make =
      (
        ~onGetCurrentPageNumber,
        ~onGetRotation,
        ~onSetRotation,
        ~onSetCurrentPageNumber,
        ~onScrollPageIntoView,
        ()
      ) => {
    let _make:
      (unit => int, int => Js.boolean, unit => int, int => Js.boolean, 'a) => t = [%raw
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
        ~destArray=ev##destArray,
        ()
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
  external make : unit => t = "PDFLinkService";
  [@bs.send.pipe : t] external setDocument : (Document.t, string) => unit = "";
  [@bs.send.pipe : t] external setViewer : Viewer.t => unit = "";
};

type t = PdfLinkService.t;

let make = (~viewer, ~pdfDocument, ~baseUrl, ()) : t =>
  PdfLinkService.(
    make() *> setDocument(pdfDocument, baseUrl) *> setViewer(viewer)
  );