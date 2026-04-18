(* ---- Mean ---- *)
let calculate_mean lst =
  let sum   = List.fold_left (+) 0 lst in
  let count = List.length lst in
  float_of_int sum /. float_of_int count

(* ---- Median ---- *)
let calculate_median lst =
  let sorted = List.sort compare lst in
  let n = List.length sorted in
  if n mod 2 = 0 then
    let a = List.nth sorted (n / 2 - 1) in
    let b = List.nth sorted (n / 2) in
    (float_of_int a +. float_of_int b) /. 2.0
  else
    float_of_int (List.nth sorted (n / 2))

(* ---- Mode ---- *)
(* Build a frequency association list [(value, count); ...] *)
let build_freq lst =
  List.fold_left
    (fun acc x ->
       match List.assoc_opt x acc with
       | None   -> (x, 1) :: acc
       | Some c -> (x, c + 1) :: List.filter (fun (k, _) -> k <> x) acc)
    [] lst

let calculate_mode lst =
  let freq     = build_freq lst in
  let max_freq = List.fold_left (fun acc (_, c) -> max acc c) 0 freq in
  let modes    = List.filter_map
                   (fun (v, c) -> if c = max_freq then Some v else None)
                   freq in
  List.sort compare modes

(* ---- Helpers for printing ---- *)
let print_list sep fmt lst =
  let rec aux = function
    | []      -> ()
    | [x]     -> Printf.printf "%s" (fmt x)
    | x :: tl -> Printf.printf "%s%s" (fmt x) sep; aux tl
  in aux lst

(* ---- Main ---- *)
let () =
  let data = [4; 1; 2; 2; 3; 5; 3; 3; 7; 1] in

  print_string "Data:   ";
  print_list ", " string_of_int data;
  print_newline ();

  Printf.printf "Mean:   %.2f\n" (calculate_mean data);
  Printf.printf "Median: %.2f\n" (calculate_median data);

  print_string "Mode:   ";
  print_list ", " string_of_int (calculate_mode data);
  print_newline ()
