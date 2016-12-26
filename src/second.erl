-module(second).
-export([check/1]).
-on_load(init/0).
-version("0.0.0").

init() ->
  SoName = filename:join(case code:priv_dir(?MODULE) of
                           {error, bad_name} ->
                              filename:join([filename:dirname(code:which(?MODULE)), "..", "priv"]);
                           Dir ->
                              Dir
                         end, atom_to_list(?MODULE)),
  case erlang:load_nif(SoName, 0) of
    ok -> ok;
    {error, E} -> error_logger:error_msg("nif load error: ~p\n", [E])
  end,
  ok.



check(_B) -> {error, not_implemented}.
