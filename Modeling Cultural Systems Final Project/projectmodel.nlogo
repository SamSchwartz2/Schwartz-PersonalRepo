turtles-own [
  price               ; How much each candidate charges for its product
  initial-area-count
  area-count          ; The area (market share) that a candidate held at the end of the last tick
  distances-list      ; adjancency list
  strategy            ; strategy, gonna be either All-P, All-A, TFT, Random
  score   ;;temporary var im using to make sure that playing the game works
  initial-y

]

patches-own [
  preferred-candidate     ; The candidate currently preferred by the voter
]

globals [
  payoffVal ;;# of patches candidates gain or lose
  strategies
  voters
  threshold
  first?
  totLinks ;;total number of links
  stmtCheck
  dispCounter ;;making sure initial max stays initial
  maximum-initial
  winner-strat
  winner-init-area
  winner-init-y
  ;;maxArea
  ; The patches that will act as voters, either a vertical line or all patches
]

links-own [history] ; History of interactions between turtles

;;;;;;;;;;;;;;;;;;;;;;;;
;;; setup procedures ;;;
;;;;;;;;;;;;;;;;;;;;;;;;

to setup
  clear-all
  setup-voters
  set strategies [ "All-Promote" "All-Attack" "Random" "TFT" ]
  set payoffVal payoff
  set stmtCheck 0
  set first? true
  setup-candidates
  setup-links
  recalculate-area
  ask turtles[set initial-area-count area-count]
  ask turtles[set initial-y get-y]
  set maximum-initial initial-max
  reset-ticks
end

to setup-voters
  ; candidate the agentset of patches that are going to be our
  ; voters in a global variable for easy reference.
  let layout "line"
  set voters ifelse-value layout = "line"
    [ patches with [ pxcor = 0 ] ]
    [ patches ]
end

to setup-candidates
  ; We choose as many random colors as the number of candidates we want to create
  let colors [0 5 15 22 25 35 42 45 52 55 65 75 85 95 105 112 115 125 135 139.9]

  foreach n-of number-of-candidates colors [ c ->
    ; ...and we create a candidate of each of these colors on random voter patches
    ask one-of voters [
      sprout 1 [
        set color c ; use the color from the list that we are looping through
        set shape "Circle"
        set size 2
        set price 10
        set pen-size 5
      ]
    ]
  ]
    if first?[
     ask turtles[set strategy one-of strategies]
     set first? false]
end

to setup-links
  ;; Even though we are on a grid, it is still convenient
  ;; to track the pairwise relationships with hidden links between turtles
  ;; rather than patches

  ask turtles [
    let my-neighbor nobody
    set my-neighbor first find-nearest-turtles
   ;; ask patch-here [
     ;; ask neighbors [
      ;;  set my-neighbor ( turtle-set turtles-here my-neighbors )
     ;; ]
    create-link-with my-neighbor
  ]

  ;; each link keeps the history of the interaction of the two players as a vector
  ;; initiatize this history vector [ ]
  ask links
  [
    set history [ ]
    set hidden? true
  ]
  set totLinks count links

end

;;to setup-strategies
  ;;set strategies [ "All-Promote" "All-Attack" "Random" "TFT" ]
  ;;ask turtles[set strategy one-of strategies]
;;end


to go
  ; We accumulate location and price changes as lists of tasks to be run later
  ; in order to simulate simultaneous decision making on the part of the candidates
  let rules "moving-only"
  let location-changes ifelse-value rules = "pricing-only"
   [ (list) ] ; if we are doing "pricing-only", the list of moves is empty
   [ [ new-location-task ] of turtles ]

  foreach location-changes run

  ask turtles[
    set distances-list find-nearest-turtles
  ]
    ask links
  [
    ;; we want to track the players
    ;; for consistency, we will call "player1" the player with the LOWER who number
    ;; and player2 the player with the HIGHER who number
    let player1 one-of both-ends
    let player2 one-of both-ends with [ self != player1 ]
    if [who] of player1 > [who] of player2
    [
      let temp player1
      set player1 player2
      set player2 temp
    ]

    ;; Next, determine the actions of each player on this round of play
    ;; To do so, we will call an "action" procedure  and pass it  the player and
    ;; the history of the relationship
    let player-1-history map first history ;; this is a list of player 1's actions
    let player-2-history map last history ;; this is a list of player 2's actions
    let action1 get-action player1 player-1-history player-2-history ;; Reports player 1's action
    let action2 get-action player2 player-2-history player-1-history ;; Reports player 2's action

    ;;winner should gain 3 patches from losers total
    ;;look something like this:
    ;;int count = 0
    ;;if losers area < 3 [ they die, give all their voters to winner ]
    ;;else [
    ;;     while count <= 3 [
    ;;           ask voters [
    ;;               if pcolor = color of loser [
    ;;                     set preferred candidate to winner
    ;;                     set pcolor to pcolor of winner
    ;;                     count++
    ;;               ]
    ;;            ]
    ;;      ]
    ;;     recalculate area



    ;; Case 1: both self promote
    if action1 = "P" and action2 = "P"
    [
      ;;ask player1 [ set score (score + 1) ]
      ;;ask player2 [ set score (score + 1) ]
      set history ( lput [ "P" "P" ] history )
    ]

    ;; Case 2: both attack
    if action1 = "A" and action2 = "A"
    [
      let outcomes [3 -3]
      let p1outcome one-of outcomes
      let p2outcome p1outcome * -1

      ask player1 [ set score (score + p1outcome ) ]
      ask player2 [ set score (score + p2outcome ) ]
      set history ( lput [ "A" "A" ] history )
      ifelse p1outcome > 0[
         let voterset (voters with [pcolor = ([color] of player2 + 2)])
         ask up-to-n-of payoffVal voterset [
         set stmtCheck stmtCheck + 1
         set preferred-candidate player1
         set pcolor ([ color ] of preferred-candidate + 2)
         ;;set pcolor white
        ]
      ]
      [
         let voterset (voters with [pcolor = ([color] of player1 + 2)])
         ask up-to-n-of payoffVal voterset [
         set stmtCheck stmtCheck + 1
         set preferred-candidate player2
         set pcolor ([ color ] of preferred-candidate + 2)
         ;;set pcolor white
        ]
      ]
    ]


    ;; Case 3: promote - attack
    if action1 = "P" and action2 = "A"
    [
      ask player1 [set score (score - payoffVal)]
      ask player2 [ set score (score + payoffVal)]
      set history ( lput [ "P" "A" ] history )
      ;;while [counter < 4]
      ;;[
      ;;ask voters [
          let voterset (voters with [pcolor = ([color] of player1 + 2)])
          ask up-to-n-of payoffVal voterset [
            set stmtCheck stmtCheck + 1
            set preferred-candidate player2
            set pcolor ([ color ] of preferred-candidate + 2)
            ;;set pcolor white
          ;;]
      ;;  set counter counter + 1
      ]
    ]
    ;; Case 4: attack - promote
    if action1 = "A" and action2 = "P"
    [
      ask player1 [set score (score + payoffVal)]
      ask player2 [ set score (score - payoffVal)]
      set history ( lput [ "A" "P" ] history )
      ;;while [counter < 4]
      ;;[
      ;;  ask voters [
          let voterset (voters with [pcolor = ([color] of player2 + 2 )])
          ask up-to-n-of payoffVal voterset [
            set stmtCheck stmtCheck + 1
            set preferred-candidate player1
            set pcolor ([ color ] of preferred-candidate + 2)
            ;;set pcolor white
         ;; ]
         ;; if pcolor = ([color] of player2 + 2) [
           ;; set stmtCheck stmtCheck + 1
            ;;set preferred-candidate player1
            ;;set pcolor ([ color ] of preferred-candidate + 2)

          ]
          ;;set counter counter + 1
        ]
      ]

   ask turtles [
    set area-count count voters with [ preferred-candidate = myself ]
   ;; set area-count count voters with [pcolor = [color] of myself]
  ]



 ;; foreach location-changes run
  ;;if count turtles < 3[stop]
  ;;recalculate-area
  if count turtles < 3[
    recalculate-area
    stop
  ]
  ask turtles[
    if [area-count] of self = maxArea[
      set winner-strat strategy
      set winner-init-area initial-area-count
      set winner-init-y initial-y
  ] ]
  tick
    if ticks mod 3 = 0 [
    eliminate-candidates
    recalculate-area
  ]
end


to-report get-action [ player my-history opponent-history ]

  if [strategy] of player = "All-Promote"
  [ report "P" ]

  if [strategy] of player = "All-Attack"
  [ report "A" ]

  if [strategy] of player = "Random"
  [
    let random-move one-of [ "P" "A" ]
    report random-move
  ]

  if [strategy] of player = "TFT"
  [ report play-TFT player my-history opponent-history ]


end



to recalculate-area
  ; Have each voter (patch) indicate its preference by
  ; taking on the color of the candidate it chooses
  ask voters [
    set preferred-candidate choose-candidate
    set pcolor ([ color ] of preferred-candidate + 2)
  ]
  ask turtles [
    set area-count count voters with [ preferred-candidate = myself ]
   ;; set area-count count voters with [pcolor = [color] of myself]
  ]
end



to-report find-nearest-turtles
  ;; report a sorted list of turtles based on the distance from the given-turtle

  let sorted-distances []
  ask self[
    set sorted-distances sort-on [distance myself] turtles with [ self != myself ] ]
  report sorted-distances


end


to-report play-TFT [ player my-history opponent-history ]

  (ifelse ( empty? opponent-history )
    ;; TFT begins by cooperating in period 0
    [ report "P" ]
    ;; otherwise, do the last thing your opponent did
    [ report last opponent-history ])

end



to eliminate-candidates
  ;loop through turtles
  ;if area-count (number of voters) is less than threshold, die (drop out)
  let totTurtles count turtles
  ;;if totTurtles < 3 [stop]
  set threshold min [area-count] of turtles
  ask turtles[
    if area-count = threshold[die]
  ]
  ;;set threshold 100 / (totTurtles + 1)

;;  ask turtles[
  ;;    if area-count <= threshold [
  ;;    die
   ;; ]
  ;;]

end

;;;;;;;;;;;;;;;;;;;;;;;;;
;;; turtle procedures ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;

; Have the candidate consider the benefits of taking a unit step in each of the four cardinal directions
; and report a task that will allow the chosen location change to be enacted later
to-report new-location-task

  ; Use `[ self ] of` to turn the `neighbors4` agentset into a shuffled list
  let possible-moves [ self ] of neighbors4 with [ member? self voters ]

  if area-count > 0 [
    ; Only consider the status quo if we already have a market share, but if we consider it,
    ; put it at the front of the list so it is favored in case of ties in sort-by
    set possible-moves fput patch-here possible-moves
  ]

  ; pair the potential moves with their market shares, and sort these pairs by market share
  let moves-with-market-shares
    sort-by [ [a b] -> last a > last b ]
    map [ move -> list move (market-share-if-move-to move) ] possible-moves

  ; report the first item of the first pair, i.e., the move with the best market share
  let chosen-location first first moves-with-market-shares

  let candidate self ; put self in a local variable so that it can be "captured" by the task
  report [ ->
    ask candidate [
      pen-down
      move-to chosen-location
      pen-up
    ]
  ]
end

; report the market share area the candidate would have if it moved to destination
to-report market-share-if-move-to [ destination ] ; turtle procedure
  let current-position patch-here
  move-to destination
  let market-share-at-destination potential-market-share
  move-to current-position
  report market-share-at-destination
end

to-report potential-market-share
  report count voters with [ choose-candidate = myself ]
end

; Have the candidate consider the revenue from hypothetically increasing or decreasing its price by one unit
; and report a task that will allow the chosen price change to be enacted later


;;;;;;;;;;;;;;;;;;;;;;;
;;; patch procedure ;;;
;;;;;;;;;;;;;;;;;;;;;;;

; report the candidate with the best deal, defined as the smallest sum of price and distance

to-report choose-candidate
  report min-one-of turtles [distance myself]
end



;;reporters for behavior space


to-report get-score
  report score
end

to-report initial-max
  report max-one-of turtles [area-count]
end

to-report maxArea
  report max [area-count] of turtles
end

to-report get-iac
  report initial-area-count
end

to-report get-ac
  report area-count
end

to-report winning-strategy
  ;;set winner-strat (strategy of (max-one-of turtles [area-count]))
end

to-report get-y
  report ycor
end




; Copyright 2009 Uri Wilensky.
; See Info tab for full copyright and license.
@#$#@#$#@
GRAPHICS-WINDOW
355
11
790
727
-1
-1
7.0
1
10
1
1
1
0
1
0
1
-30
30
-50
50
0
0
1
ticks
30.0

SLIDER
13
42
176
75
number-of-candidates
number-of-candidates
10
20
10.0
1
1
NIL
HORIZONTAL

BUTTON
236
43
302
76
NIL
setup
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
236
152
299
185
NIL
go
T
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
227
95
308
128
go once
go
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

PLOT
873
15
1097
197
Candidates Remaining
NIL
NIL
0.0
10.0
0.0
20.0
true
false
"" ""
PENS
"default" 1.0 0 -16777216 true "" "plot count turtles"

PLOT
874
226
1099
405
Vote Threshold
NIL
NIL
0.0
10.0
0.0
50.0
true
false
"" ""
PENS
"default" 1.0 0 -16777216 true "" "plot 100 / count turtles"

MONITOR
30
290
288
335
Candidate with highest initial vote share
maximum-initial
17
1
11

MONITOR
36
388
257
433
Candidate with highest vote share
initial-max
17
1
11

MONITOR
66
451
218
496
% vote share for leader
maxArea
17
1
11

MONITOR
49
530
250
575
Strategy of current vote leader
winner-strat
17
1
11

SLIDER
0
200
354
233
payoff
payoff
1
5
5.0
1
1
+\- votes gained\lost per attack
HORIZONTAL

@#$#@#$#@
## WHAT IS IT?

(a general understanding of what the model is trying to show or explain)

## HOW IT WORKS

(what rules the agents use to create the overall behavior of the model)

## HOW TO USE IT

(how to use the model, including a description of each of the items in the Interface tab)

## THINGS TO NOTICE

(suggested things for the user to notice while running the model)

## THINGS TO TRY

(suggested things for the user to try to do (move sliders, switches, etc.) with the model)

## EXTENDING THE MODEL

(suggested things to add or change in the Code tab to make the model more complicated, detailed, accurate, etc.)

## NETLOGO FEATURES

(interesting or unusual features of NetLogo that the model uses, particularly in the Code tab; or where workarounds were needed for missing features)

## RELATED MODELS

(models in the NetLogo Models Library and elsewhere which are of related interest)

## CREDITS AND REFERENCES

(a reference to the model's URL on the web if it has one, as well as any other necessary credits, citations, and links)
@#$#@#$#@
default
true
0
Polygon -7500403 true true 150 5 40 250 150 205 260 250

airplane
true
0
Polygon -7500403 true true 150 0 135 15 120 60 120 105 15 165 15 195 120 180 135 240 105 270 120 285 150 270 180 285 210 270 165 240 180 180 285 195 285 165 180 105 180 60 165 15

arrow
true
0
Polygon -7500403 true true 150 0 0 150 105 150 105 293 195 293 195 150 300 150

box
false
0
Polygon -7500403 true true 150 285 285 225 285 75 150 135
Polygon -7500403 true true 150 135 15 75 150 15 285 75
Polygon -7500403 true true 15 75 15 225 150 285 150 135
Line -16777216 false 150 285 150 135
Line -16777216 false 150 135 15 75
Line -16777216 false 150 135 285 75

bug
true
0
Circle -7500403 true true 96 182 108
Circle -7500403 true true 110 127 80
Circle -7500403 true true 110 75 80
Line -7500403 true 150 100 80 30
Line -7500403 true 150 100 220 30

butterfly
true
0
Polygon -7500403 true true 150 165 209 199 225 225 225 255 195 270 165 255 150 240
Polygon -7500403 true true 150 165 89 198 75 225 75 255 105 270 135 255 150 240
Polygon -7500403 true true 139 148 100 105 55 90 25 90 10 105 10 135 25 180 40 195 85 194 139 163
Polygon -7500403 true true 162 150 200 105 245 90 275 90 290 105 290 135 275 180 260 195 215 195 162 165
Polygon -16777216 true false 150 255 135 225 120 150 135 120 150 105 165 120 180 150 165 225
Circle -16777216 true false 135 90 30
Line -16777216 false 150 105 195 60
Line -16777216 false 150 105 105 60

car
false
0
Polygon -7500403 true true 300 180 279 164 261 144 240 135 226 132 213 106 203 84 185 63 159 50 135 50 75 60 0 150 0 165 0 225 300 225 300 180
Circle -16777216 true false 180 180 90
Circle -16777216 true false 30 180 90
Polygon -16777216 true false 162 80 132 78 134 135 209 135 194 105 189 96 180 89
Circle -7500403 true true 47 195 58
Circle -7500403 true true 195 195 58

circle
false
0
Circle -7500403 true true 0 0 300

circle 2
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240

cow
false
0
Polygon -7500403 true true 200 193 197 249 179 249 177 196 166 187 140 189 93 191 78 179 72 211 49 209 48 181 37 149 25 120 25 89 45 72 103 84 179 75 198 76 252 64 272 81 293 103 285 121 255 121 242 118 224 167
Polygon -7500403 true true 73 210 86 251 62 249 48 208
Polygon -7500403 true true 25 114 16 195 9 204 23 213 25 200 39 123

cylinder
false
0
Circle -7500403 true true 0 0 300

dot
false
0
Circle -7500403 true true 90 90 120

face happy
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 255 90 239 62 213 47 191 67 179 90 203 109 218 150 225 192 218 210 203 227 181 251 194 236 217 212 240

face neutral
false
0
Circle -7500403 true true 8 7 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Rectangle -16777216 true false 60 195 240 225

face sad
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 168 90 184 62 210 47 232 67 244 90 220 109 205 150 198 192 205 210 220 227 242 251 229 236 206 212 183

fish
false
0
Polygon -1 true false 44 131 21 87 15 86 0 120 15 150 0 180 13 214 20 212 45 166
Polygon -1 true false 135 195 119 235 95 218 76 210 46 204 60 165
Polygon -1 true false 75 45 83 77 71 103 86 114 166 78 135 60
Polygon -7500403 true true 30 136 151 77 226 81 280 119 292 146 292 160 287 170 270 195 195 210 151 212 30 166
Circle -16777216 true false 215 106 30

flag
false
0
Rectangle -7500403 true true 60 15 75 300
Polygon -7500403 true true 90 150 270 90 90 30
Line -7500403 true 75 135 90 135
Line -7500403 true 75 45 90 45

flower
false
0
Polygon -10899396 true false 135 120 165 165 180 210 180 240 150 300 165 300 195 240 195 195 165 135
Circle -7500403 true true 85 132 38
Circle -7500403 true true 130 147 38
Circle -7500403 true true 192 85 38
Circle -7500403 true true 85 40 38
Circle -7500403 true true 177 40 38
Circle -7500403 true true 177 132 38
Circle -7500403 true true 70 85 38
Circle -7500403 true true 130 25 38
Circle -7500403 true true 96 51 108
Circle -16777216 true false 113 68 74
Polygon -10899396 true false 189 233 219 188 249 173 279 188 234 218
Polygon -10899396 true false 180 255 150 210 105 210 75 240 135 240

house
false
0
Rectangle -7500403 true true 45 120 255 285
Rectangle -16777216 true false 120 210 180 285
Polygon -7500403 true true 15 120 150 15 285 120
Line -16777216 false 30 120 270 120

leaf
false
0
Polygon -7500403 true true 150 210 135 195 120 210 60 210 30 195 60 180 60 165 15 135 30 120 15 105 40 104 45 90 60 90 90 105 105 120 120 120 105 60 120 60 135 30 150 15 165 30 180 60 195 60 180 120 195 120 210 105 240 90 255 90 263 104 285 105 270 120 285 135 240 165 240 180 270 195 240 210 180 210 165 195
Polygon -7500403 true true 135 195 135 240 120 255 105 255 105 285 135 285 165 240 165 195

line
true
0
Line -7500403 true 150 0 150 300

line half
true
0
Line -7500403 true 150 0 150 150

pentagon
false
0
Polygon -7500403 true true 150 15 15 120 60 285 240 285 285 120

person
false
0
Circle -7500403 true true 110 5 80
Polygon -7500403 true true 105 90 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285 180 195 195 90
Rectangle -7500403 true true 127 79 172 94
Polygon -7500403 true true 195 90 240 150 225 180 165 105
Polygon -7500403 true true 105 90 60 150 75 180 135 105

plant
false
0
Rectangle -7500403 true true 135 90 165 300
Polygon -7500403 true true 135 255 90 210 45 195 75 255 135 285
Polygon -7500403 true true 165 255 210 210 255 195 225 255 165 285
Polygon -7500403 true true 135 180 90 135 45 120 75 180 135 210
Polygon -7500403 true true 165 180 165 210 225 180 255 120 210 135
Polygon -7500403 true true 135 105 90 60 45 45 75 105 135 135
Polygon -7500403 true true 165 105 165 135 225 105 255 45 210 60
Polygon -7500403 true true 135 90 120 45 150 15 180 45 165 90

sheep
false
15
Circle -1 true true 203 65 88
Circle -1 true true 70 65 162
Circle -1 true true 150 105 120
Polygon -7500403 true false 218 120 240 165 255 165 278 120
Circle -7500403 true false 214 72 67
Rectangle -1 true true 164 223 179 298
Polygon -1 true true 45 285 30 285 30 240 15 195 45 210
Circle -1 true true 3 83 150
Rectangle -1 true true 65 221 80 296
Polygon -1 true true 195 285 210 285 210 240 240 210 195 210
Polygon -7500403 true false 276 85 285 105 302 99 294 83
Polygon -7500403 true false 219 85 210 105 193 99 201 83

square
false
0
Rectangle -7500403 true true 30 30 270 270

square 2
false
0
Rectangle -7500403 true true 30 30 270 270
Rectangle -16777216 true false 60 60 240 240

star
false
0
Polygon -7500403 true true 151 1 185 108 298 108 207 175 242 282 151 216 59 282 94 175 3 108 116 108

target
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240
Circle -7500403 true true 60 60 180
Circle -16777216 true false 90 90 120
Circle -7500403 true true 120 120 60

tree
false
0
Circle -7500403 true true 118 3 94
Rectangle -6459832 true false 120 195 180 300
Circle -7500403 true true 65 21 108
Circle -7500403 true true 116 41 127
Circle -7500403 true true 45 90 120
Circle -7500403 true true 104 74 152

triangle
false
0
Polygon -7500403 true true 150 30 15 255 285 255

triangle 2
false
0
Polygon -7500403 true true 150 30 15 255 285 255
Polygon -16777216 true false 151 99 225 223 75 224

truck
false
0
Rectangle -7500403 true true 4 45 195 187
Polygon -7500403 true true 296 193 296 150 259 134 244 104 208 104 207 194
Rectangle -1 true false 195 60 195 105
Polygon -16777216 true false 238 112 252 141 219 141 218 112
Circle -16777216 true false 234 174 42
Rectangle -7500403 true true 181 185 214 194
Circle -16777216 true false 144 174 42
Circle -16777216 true false 24 174 42
Circle -7500403 false true 24 174 42
Circle -7500403 false true 144 174 42
Circle -7500403 false true 234 174 42

turtle
true
0
Polygon -10899396 true false 215 204 240 233 246 254 228 266 215 252 193 210
Polygon -10899396 true false 195 90 225 75 245 75 260 89 269 108 261 124 240 105 225 105 210 105
Polygon -10899396 true false 105 90 75 75 55 75 40 89 31 108 39 124 60 105 75 105 90 105
Polygon -10899396 true false 132 85 134 64 107 51 108 17 150 2 192 18 192 52 169 65 172 87
Polygon -10899396 true false 85 204 60 233 54 254 72 266 85 252 107 210
Polygon -7500403 true true 119 75 179 75 209 101 224 135 220 225 175 261 128 261 81 224 74 135 88 99

wheel
false
0
Circle -7500403 true true 3 3 294
Circle -16777216 true false 30 30 240
Line -7500403 true 150 285 150 15
Line -7500403 true 15 150 285 150
Circle -7500403 true true 120 120 60
Line -7500403 true 216 40 79 269
Line -7500403 true 40 84 269 221
Line -7500403 true 40 216 269 79
Line -7500403 true 84 40 221 269

wolf
false
0
Polygon -16777216 true false 253 133 245 131 245 133
Polygon -7500403 true true 2 194 13 197 30 191 38 193 38 205 20 226 20 257 27 265 38 266 40 260 31 253 31 230 60 206 68 198 75 209 66 228 65 243 82 261 84 268 100 267 103 261 77 239 79 231 100 207 98 196 119 201 143 202 160 195 166 210 172 213 173 238 167 251 160 248 154 265 169 264 178 247 186 240 198 260 200 271 217 271 219 262 207 258 195 230 192 198 210 184 227 164 242 144 259 145 284 151 277 141 293 140 299 134 297 127 273 119 270 105
Polygon -7500403 true true -1 195 14 180 36 166 40 153 53 140 82 131 134 133 159 126 188 115 227 108 236 102 238 98 268 86 269 92 281 87 269 103 269 113

x
false
0
Polygon -7500403 true true 270 75 225 30 30 225 75 270
Polygon -7500403 true true 30 75 75 30 270 225 225 270
@#$#@#$#@
NetLogo 6.2.2
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
<experiments>
  <experiment name="experiment" repetitions="100" runMetricsEveryStep="false">
    <setup>setup</setup>
    <go>go</go>
    <metric>maximum-initial</metric>
    <metric>initial-max</metric>
    <metric>maxArea</metric>
    <metric>winner-strat</metric>
    <metric>winner-init-area</metric>
    <metric>winner-init-y</metric>
    <enumeratedValueSet variable="number-of-candidates">
      <value value="10"/>
      <value value="15"/>
      <value value="20"/>
    </enumeratedValueSet>
  </experiment>
</experiments>
@#$#@#$#@
@#$#@#$#@
default
0.0
-0.2 0 0.0 1.0
0.0 1 1.0 0.0
0.2 0 0.0 1.0
link direction
true
0
Line -7500403 true 150 150 90 180
Line -7500403 true 150 150 210 180
@#$#@#$#@
0
@#$#@#$#@
