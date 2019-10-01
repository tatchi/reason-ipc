// https://ocaml.github.io/ocamlunix/pipes.html
// https://caml.inria.fr/pub/docs/oreilly-book/html/book-ora168.html

let main = () => {
  let (fd_in, fd_out) = Lwt_unix.pipe();
  // let processIn =
  //   Lwt_process.open_process_none(
  //     // ~stdin=`FD_move(Lwt_unix.unix_file_descr(fd_in)),
  //     ~stdout=`FD_move(Lwt_unix.unix_file_descr(fd_out)),
  //     ("", [|"ls", "-l"|]),
  //   );

  Lwt_io.write_line(Lwt_io.of_fd(Output, fd_out), "hello") |> ignore;

  Lwt.bind(
    Lwt_io.read_line(Lwt_io.of_fd(Input, fd_in)),
    res => {
      Console.log(res);
      Lwt.return();
    },
  );
};

Lwt_main.run(main());