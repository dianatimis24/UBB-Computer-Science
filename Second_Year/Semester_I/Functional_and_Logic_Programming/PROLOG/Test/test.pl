% prime(N, D) = 
%   True, if N <= D
%   prime(N, D + 1), if N % D != 0
% prime(i, i)
prime(N, D):- N =< D, !.
prime(N, D):- N mod D =\= 0, D1 is D + 1, prime(N, D1).

% Wrapper Function
% prime(N) = 
%   False, if N < 2
%   prime(N, 2), otherwise
% prime(i)
prime(N):-N >= 2, prime(N, 2).

% prime_list(l1l2...ln) = 
%   [], if n == 0
%   l1 U prime_list(l2...ln), if prime(l1) == True
%   prime_list(l2...ln), otherwise
% prime_list(i, o)
prime_list([], []).
prime_list([H|T], [H|R]):- prime(H), prime_list(T, R).
prime_list([_|T], R):- prime_list(T, R).