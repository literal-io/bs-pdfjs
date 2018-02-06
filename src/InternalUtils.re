let ( *> ) = (x, f) => {
  let _ = f(x);
  x;
};

let wrapBs = cb => [@bs] (a => cb(a));