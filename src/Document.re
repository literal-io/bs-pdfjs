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
  type url = {
    .
    "url": string,
    "httpHeaders": Js.Nullable.t(Js.Dict.t(string)),
    "withCredentials": Js.Nullable.t(bool),
  };
  type typedArray = {. "data": Js.Typed_array.Int8Array.t};
  type t =
    | Url(url)
    | TypedArray(typedArray);
  let make = (~url=?, ~data=?, ~httpHeaders=?, ~withCredentials=?, ()) =>
    switch (url, data, httpHeaders, withCredentials) {
    | (Some(url), None, _, _) =>
      Some(
        Url({
          "url": url,
          "httpHeaders": Js.Nullable.from_opt(httpHeaders),
          "withCredentials": Js.Nullable.from_opt(withCredentials),
        }),
      )
    | (None, Some(data), None, None) => Some(TypedArray({"data": data}))
    | _ => None
    };
  let url =
    fun
    | Url(inst) => Some(inst##url)
    | TypedArray(_) => None;
  let httpHeaders =
    fun
    | Url(inst) => Js.Nullable.toOption(inst##httpHeaders)
    | TypedArray(_) => None;
  let withCredentials =
    fun
    | Url(inst) => Js.Nullable.toOption(inst##withCredentials)
    | TypedArray(_) => None;
};

[@bs.send.pipe: t] external getPage : int => Js.Promise.t(Page.t) = "";

[@bs.send] external getMetadata : t => Js.Promise.t(Metadata.t) = "";

[@bs.get] external getNumPages : t => int = "numPages";

[@bs.get] external fingerprint : t => string = "";

[@bs.send]
external getData : t => Js.Promise.t(Js.Typed_array.Int8Array.t) = "";

[@bs.send] external cleanup : t => unit = "";
