type t;

module Params = {
  type t;
  [@bs.obj]
  external make :
    (
      ~get: (Js.t({..}), string) => 'a=?,
      ~set: (Js.t({..}), string, 'a) => Js.boolean=?,
      unit
    ) =>
    t =
    "";
};

[@bs.new] external make : (Params.t, Js.t({..})) => Js.t({..}) = "Proxy";