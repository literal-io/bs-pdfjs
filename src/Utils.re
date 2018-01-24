[@bs.val]
external maxCanvasPixels : Js.undefined(float) =
  "window.PDFJS.maxCanvasPixels";

[@bs.val] [@bs.module "pdfjs-dist/lib/web/ui_utils.js"]
external getPDFFileNameFromURL : string => string = "";