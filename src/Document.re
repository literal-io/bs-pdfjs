open InternalUtils;

type t;

module Metadata = {
  type t = {
    .
    "metadata": Js.Json.t,
    "info": Js.Nullable.t(Js.Dict.t(string)),
  };
  let getTitle = (metadata: t) =>
    Js.toOption(metadata##info)
    |> Js.Option.andThen(wrapBs(info => Js.Dict.get(info, "Title")));
  let getAuthor = (metadata: t) =>
    Js.toOption(metadata##info)
    |> Js.Option.andThen(wrapBs(info => Js.Dict.get(info, "Author")));
};

module Source = {
  [@bs.deriving abstract]
  type urlSource = {
    url: string,
    [@bs.optional]
    httpHeaders: Js.Dict.t(string),
    [@bs.optional]
    withCredentials: bool,
    [@bs.optional]
    worker: PdfWorker.t,
  };

  [@bs.deriving abstract]
  type typedArraySource = {
    data: Js.Typed_array.Int8Array.t,
    [@bs.optional]
    worker: PdfWorker.t,
  };

  type t =
    | Url(urlSource)
    | TypedArray(typedArraySource);

  let make =
      (~url=?, ~data=?, ~httpHeaders=?, ~withCredentials=?, ~worker=?, ()) =>
    switch (url, data, httpHeaders, withCredentials, worker) {
    | (Some(url), None, _, _, _) =>
      Some(
        Url(urlSource(~url, ~httpHeaders?, ~withCredentials?, ~worker?, ())),
      )
    | (None, Some(data), None, None, _) =>
      Some(TypedArray(typedArraySource(~data, ~worker?, ())))
    | _ => None
    };
  let url =
    fun
    | Url(inst) => inst |> urlGet |> Js.Option.some
    | TypedArray(_) => None;
  let httpHeaders =
    fun
    | Url(inst) => inst |> httpHeadersGet
    | TypedArray(_) => None;
  let withCredentials =
    fun
    | Url(inst) => inst |> withCredentialsGet
    | TypedArray(_) => None;
};

[@bs.send.pipe: t] external getPage: int => Js.Promise.t(Page.t) = "";

[@bs.send] external getMetadata: t => Js.Promise.t(Metadata.t) = "";

[@bs.get] external getNumPages: t => int = "numPages";

[@bs.get] external fingerprint: t => string = "";

[@bs.send]
external getData: t => Js.Promise.t(Js.Typed_array.Int8Array.t) = "";

[@bs.send] external cleanup: t => unit = "";
