// https://ocaml.github.io/ocamlunix/pipes.html
// https://caml.inria.fr/pub/docs/oreilly-book/html/book-ora168.html
open Lwt;

let main = () => {
  let (fd_in, fd_out) = Lwt_unix.pipe();
  let _ =
    Lwt_process.open_process_out(
      // ~stdin=`FD_move(Lwt_unix.unix_file_descr(fd_in)),
      ~stdout=`FD_move(Lwt_unix.unix_file_descr(fd_out)),
      ("", [|"fswatch", " -e '.*/\..*'", "."|]),
    );

  let stream = Lwt_io.read_lines(Lwt_io.of_fd(Input, fd_in));

  Lwt_stream.iter(res => {Console.log(res)}, stream);
};

Lwt_main.run(main());