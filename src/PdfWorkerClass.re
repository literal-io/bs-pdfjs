type t;

[@bs.deriving abstract]
type makeParams = {
  postMessageTransfers: bool,
  port: Js.Null_undefined.t(int),
  verbosity: Js.Null_undefined.t(int),
};

[@bs.new] external make: (t, makeParams) => PdfWorker.t = "";
