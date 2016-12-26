```
$ rebar compile
$ ERL_LIBS=./ erl
Erlang/OTP 19 [erts-8.0] [source] [64-bit] [smp:2:2] [async-threads:10] [hipe] [kernel-poll:false]

Eshell V8.0  (abort with ^G)
1> {ok, Bin} = first:start().
{ok,<<"frame">>}
2> {ok, frame} = first:check(Bin).
** exception error: no match of right hand side value {ok,framedata}
3> {ok, framedata} = first:check(Bin).
{ok,framedata}
4> {ok, framedata} = second:check(Bin).
** exception error: bad argument
     in function  second:check/1
        called as second:check(<<"frame">>)
```