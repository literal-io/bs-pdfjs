[@bs.val] [@bs.module "pdfjs-dist/lib/web/ui_utils.js"]
external getPDFFileNameFromURL: string => string = "";

type util = {
  .
  [@bs.meth]
  "transform": (Js.Array.t(float), Js.Array.t(float)) => Js.Array.t(float),
};

[@bs.module "pdfjs-dist"] external util: util = "Util";