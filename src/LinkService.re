open InternalUtils;

module Destination = {
  type t;
};

module Viewer = {
  type t = {
    .
    [@bs.set] "currentPageNumber": int,
    [@bs.set] "rotation": int,
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
    let initial = {
      "currentPageNumber": onGetCurrentPageNumber(),
      "rotation": onGetRotation(),
      "scrollPageIntoView": ev =>
        onScrollPageIntoView(
          ~pageNumber=ev##pageNumber,
          ~destArray=ev##destArray,
          ()
        )
    };
    let proxy =
      Proxy.(
        make(
          Params.make(
            ~get=
              (obj, prop) =>
                switch prop {
                | "currentPageNumber" => onGetCurrentPageNumber()
                | "rotation" => onGetRotation()
                | "scrollPageIntoView" => obj##scrollPageIntoView
                | _ => Js.undefined
                },
            ~set=
              (obj, prop, value) =>
                switch prop {
                | "currentPageNumber" =>
                  onSetCurrentPageNumber(value);
                  Js.true_;
                | "rotation" =>
                  onSetRotation(value);
                  Js.true_;
                | _ => Js.false_
                },
            ()
          ),
          initial
        )
      );
    ();
  };
};

/**
 * Internal LinkService bindings
 *
 * TODO: is pdfHistory necessary?
 * */
module PdfLinkService = {
  type t;
  [@bs.new] [@bs.module "pdfjs-dist/web/pdf_link_service"]
  external make : unit => t = "PDFLinkService";
  [@bs.send.pipe : t] external setDocument : (Document.t, string) => unit = "";
  [@bs.send.pipe : t] external setViewer : Viewer.t => unit = "";
};

type t = PdfLinkService.t;

let make = (~viewer, ~pdfDocument, ~baseUrl, ()) : t =>
  PdfLinkService.(
    make() *> setDocument(pdfDocument, baseUrl) *> setViewer(viewer)
  );