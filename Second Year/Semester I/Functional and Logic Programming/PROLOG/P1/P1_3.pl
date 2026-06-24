% 3.
% a. Define a predicate to remove from a list all repetitive elements.
% Eg.: l=[1,2,1,4,1,3,4] => l=[2,3]
% b. Remove all occurrence of a maximum value from a list on integer numbers.

% a.

% remove(L1...Ln, E) =
%  [], n == 0
%  {L1} U remove(L2...Ln, E), l1 != E
%  remove(L2...Ln, E), otherwise
% remove(i, i, o)
remove([], _, []).
remove([H|T], H, R):- remove(T, H, R).
remove([H|T], E, [H|R]):- H =\= E, remove(T, E, R).

% count_occurrences(L1...Ln, E) = 
%  0, n == 0
%  1 + count_occurrences(L2...Ln, E), E == L1
%  count_occurrences(L2...Ln), E != L1
% count_occurrences(i, i, o)
count_occurrences([], _, 0).
count_occurrences([H|T], H, R):- count_occurrences(T, H, R1), R is R1 + 1.
count_occurrences([H|T], E, R):- H =\= E, count_occurrences(T, E, R).

% remove_all(L1...Ln) = 
%  [], n == 0
%  remove_all(L2...Ln), L1 != Li, i = 2...n
%  remove_all(remove(L2...Ln)), otherwise
% remove_all(i, o)
remove_all([], []).
remove_all([H|T], [H|R]):- count_occurrences(T, H, C), C =:= 0, remove_all(T, R).
remove_all([H|T], R):- count_occurrences(T, H, C), C =\= 0, remove([H|T], H, R1), remove_all(R1, R).


% b.

% max(L1...Ln) =
%  -1.0Inf, n == 0
%  L1, l1 > max(L2...Ln)
%  max(L2...Ln), l1 =< max(L2...Ln)
% max(i, o)
max([], -1.0Inf).
max([H|T], R):- max(T, R1), H > R1, R is H.
max([H|T], R):- max(T, R1), H =< R1, R is R1.

% remove_max(L1...Ln) = 
%  [], n == 0
%  remove(L1...Ln, max(L1...Ln)), otherwise
% remove_max(i, o)
remove_max([], []).
remove_max(L, R):- max(L, MAX), remove(L, MAX, R).