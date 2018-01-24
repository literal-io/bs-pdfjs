open InternalUtils;

type t;

module Metadata = {
  type t = {
    .
    "metadata": Js.Json.t,
    "info": Js.Nullable.t(Js.Dict.t(string))
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
    "httpHeaders": Js.Nullable.t(Js.Dict.t(string))
  };
  type typedArray = {. "data": Js.Typed_array.Int8Array.t};
  type t =
    | Url(url)
    | TypedArray(typedArray);
  let make = (~url=?, ~data=?, ~httpHeaders=?, ()) =>
    switch (url, data, httpHeaders) {
    | (Some(url), None, _) =>
      Some(Url({"url": url, "httpHeaders": Js.Nullable.from_opt(httpHeaders)}))
    | (None, Some(data), None) => Some(TypedArray({"data": data}))
    | _ => None
    };
};

[@bs.send.pipe : t] external getPage : int => Js.Promise.t(Page.t) = "";

[@bs.send] external getMetadata : t => Js.Promise.t(Metadata.t) = "";

[@bs.get] external getNumPages : t => int = "numPages";

[@bs.send]
external getData : t => Js.Promise.t(Js.Typed_array.Int8Array.t) = "";