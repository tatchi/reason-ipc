// https://ocaml.github.io/ocamlunix/pipes.html
// https://caml.inria.fr/pub/docs/oreilly-book/html/book-ora168.html

let inChannel = Unix.open_process_in("ls");
// Console.log(in_channel_length(inChannel));
// let fd_in = Unix.descr_of_in_channel(inChannel)

// let res = input_line(inChannel);

// let buff = Bytes.create(100);
// Unix.read(fd_in, buff, 0, 100);

let res = ref("");


try(
  while (true) {
    res := res^ ++ "\n" ++ input_line(inChannel);
  }
) {
| End_of_file => Console.log(res^)
}