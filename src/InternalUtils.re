let ( *> ) = (x, f) => {
  let _ = f(x);
  x;
};

let wrapBs = cb => (. a) => cb(a);