% 7. 
% A player wants to choose the predictions for 4 games. The predictions can be 1, X, 2. 
% Write a predicate to generate all possible variants considering that: 
% last prediction can’t be 2 and no more than two possible predictions X.


% The total number of correct solutions:
% Case 1: two X's
%  - Subcase 1: one X is on the last position
%   - 2 free positions, on which we can place only 1's and 2's with no restrictions
%   - 3 possibilities to place the other X and the other possible combinations are: (1, 1), (1, 2), (2, 1), (2, 2)
%   => 3 * 4 = 12 solutions when we have two X's and one of them is on the last position
%   
%  - Subcase 2: no X on the last position
%   - 1 on the last position => one free position, on which we can place 1 or 2
%   - 3 possibilities to place two X's
%   => 3 * 2 = 6 solutions with two X's, none on the last position
%  
% Case 2: one X 
%  - Subcase 1: X is on the last position
%   - 3 free positions, on which we can place only 1's and 2's with no restrictions
%    - 1 solution with three 2's
%    - 3 solution with two 2's
%    - 3 solutions with one 2
%    - 1 solution with no 2's
%   - 8 solutions with X on the last position
%  
%  - Subcase 2: X is not on the last position
%   - 1 on the last position, X on a position => 2 free positions, on which we can place only 1's and 2's with no restrictions
%   - 3 possibilities to place X and the other possible combinations are: (1, 1), (1, 2), (2, 1), (2, 2) 
%   => 3 * 4 = 12 solutions when X is not on the last position
%  
% Case 3: no X
%  - 1 on the last position => 3 free positions, on which we can place only 1's and 2's with no restrictions
%    - 1 solution with three 2's
%    - 3 solution with two 2's
%    - 3 solutions with one 2
%    - 1 solution with no 2's
%  - 8 solutions with no X predictions
%
% The total number of correct solution is 12 + 6 + 8 + 12 + 8 = 46.


% generate_predictions(XCount, LeftPositions) = 
%  [], if LeftPositions == 0
%  {X} U generate_predictions(XCount + 1, LeftPositions - 1), if XCount < 2 and LeftPositions > 0 
%  {1} U generate_predictions(XCount, LeftPositions - 1), if LeftPositions > 0
%  {2} U generate_predictions(XCount, LeftPositions - 1), if LeftPositions > 1
% generate_predictions(i, i, o)
generate_predictions(_, 0, []).
generate_predictions(XCount, LeftPositions, ['X'|Res]):-
    XCount < 2, 
    LeftPositions > 0, 
    XCount1 is XCount + 1, 
    LeftPositions1 is LeftPositions - 1,
    generate_predictions(XCount1, LeftPositions1, Res).
generate_predictions(XCount, LeftPositions, ['1'|Res]):-
    LeftPositions > 0,
    LeftPositions1 is LeftPositions - 1,
    generate_predictions(XCount, LeftPositions1, Res).
generate_predictions(XCount, LeftPositions, ['2'|Res]):-
    LeftPositions > 1,
    LeftPositions1 is LeftPositions - 1,
    generate_predictions(XCount, LeftPositions1, Res).

% generate_predictions() = generate_predictions(0, 4) - Wrapper function
% generate_predictions(o)
generate_predictions(Res):-generate_predictions(0, 4, Res).