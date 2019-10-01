// https://ocaml.github.io/ocamlunix/pipes.html
// https://caml.inria.fr/pub/docs/oreilly-book/html/book-ora168.html

let (fd_in, fd_out) = Unix.pipe();

switch (Unix.fork()) {
| 0 =>
  print_endline("in parent process");
  // Close write fd
  let _ = Unix.close(fd_out);
  let buff = Bytes.create(100);
  let break = ref(false);
  while (! break^) {
    switch (Unix.read(fd_in, buff, 0, Bytes.length(buff))) {
    | 0 =>
      print_endline("I have finished to read");
      print_endline(Bytes.to_string(buff));
      break := true;
    | n => print_endline("im reading " ++ string_of_int(n))
    };
  };
| pid =>
  print_endline("in child process " ++ string_of_int(pid));
  // Close read fd
  let _ = Unix.close(fd_in);
  let message = Bytes.of_string("hello world");
  let bytesWritten = Unix.write(fd_out, message, 0, Bytes.length(message));
  print_endline(
    "I have written " ++ string_of_int(bytesWritten) ++ " bytes",
  );
  Unix.close(fd_out);
  ();
};