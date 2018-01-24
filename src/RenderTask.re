type t('a) = {
  .
  "promise": Js.Promise.t('a),
  "cancel": unit => unit
};

[@bs.send] external cancel : t('a) => unit = "cancel";

[@bs.get] external promise : t('a) => Js.Promise.t('a) = "";