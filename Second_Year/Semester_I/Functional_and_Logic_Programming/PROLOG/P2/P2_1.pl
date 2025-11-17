% 1. 
% a. Sort a list with removing the double values. E.g.: [4 2 6 2 3 4] => [2 3 4 6]
% b. For a heterogeneous list, formed from integer numbers and list of numbers, write a predicate to sort every sublist with removing the doubles.
% Eg.: [1, 2, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] => [1, 2, [1, 4], 3, 6, [1, 3, 7, 9, 10], 5, [1], 7].

% a.

% split_equally(l1l2...ln) = 
%   [], [], n == 0
%   [l1], [], n == 1
%   [l1, l3, ...], [l2, l4, ...], otherwise
% split_equally(i, o, o)
split_equally([], [], []).
split_equally([X], [X], []).
split_equally([X,Y|T], [X|L], [Y|R]):-split_equally(T, L, R).

% merge(a1a2...an, b1b2...bm) = 
%  [a1, a2,..., an], m == 0
%  [b1, b2,..., bm], n == 0
%  a1 U merge(a2a3...an, b1b2...bm), a1 <= b1
%  b1 U merge(a1a2...an, b2b3...bm), a1 > b1
% merge(i, i, o)
merge(A, [], A):-!.
merge([], B, B):-!.
merge([HA|TA], [HB|TB], [HA|AnswerT]):-HA =< HB, !, merge(TA, [HB|TB], AnswerT).
merge([HA|TA], [HB|TB], [HB|AnswerT]):-HA > HB, !, merge([HA|TA], TB, AnswerT).

% merge_sort(l1l2...ln) = 
%   [], n == 0
%   [l1], n == 1
%   merge(merge_sort(l1l3...), merge_sort(l2l4...)), otherwise
% merge_sort(i, o)
merge_sort([], []).
merge_sort([X], [X]).
merge_sort(L, Result):-
    split_equally(L, LA, LB), 
    merge_sort(LA, LASorted), 
    merge_sort(LB, LBSorted), 
    merge(LASorted, LBSorted, Result).

% remove(l1l2...ln, E) =
%  [], n == 0
%  l1 U remove(l2l3...ln, E), l1 != E
%  remove(l2l3...ln, E), otherwise
% remove(i, i, o)
remove([], _, []).
remove([H|T], H, R):- remove(T, H, R).
remove([H|T], E, [H|R]):- H =\= E, remove(T, E, R).

% remove_duplicates(l1l2...ln) = 
%  [], n == 0
%  l1 U remove_duplicates(remove(l2l3...ln, l1)), otherwise  
% remove_duplicates(i, o)
remove_duplicates([], []).
remove_duplicates([H|T], [H|Res]):-remove(T, H, T1), remove_duplicates(T1, Res).

% sort_without_duplicates(l1l2...ln) =
%  [], n == 0
%  merge_sort(remove_duplicates(l1l2...ln)), otherwise
% sort_without_duplicates(i, o)
sort_without_duplicates([], []).
sort_without_duplicates(L, Res):-remove_duplicates(L, L1), merge_sort(L1, Res).


% b.

% sort_sublists(l1l2...ln) = 
%  [], n == 0
%  sort_without_duplicates(l1) U sort_sublists(l2l3...ln), l1 is list
%  l1 U sort_sublists(l2l3...ln), otherwise
% sort_sublists(i, o)
sort_sublists([], []).
sort_sublists([H|T], [AnswerH|AnswerT]):-
    is_list(H), !, 
    sort_without_duplicates(H, AnswerH), 
    sort_sublists(T, AnswerT).
sort_sublists([H|T], [H|R]):-sort_sublists(T, R).