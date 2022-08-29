# Conway's Game of life cli

## Building 

```bash
git clone https://github.com/PandeCode/gameOfLife/
cd gameOfLife
cmake -D CMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B Debug && ln -s ./Debug/compile_commands.json ./compile_commands.json  
cmake --build Debug/
```

## Examples
```bash
./Debug/bin/gameOfLife -f states/oscillators/beacon.gol
./Debug/bin/gameOfLife -f states/oscillators/blinker.gol
./Debug/bin/gameOfLife -f states/oscillators/penta_decathlon.gol
./Debug/bin/gameOfLife -f states/oscillators/pulsar.gol
./Debug/bin/gameOfLife -f states/oscillators/toad.gol

./Debug/bin/gameOfLife -f states/space_ships/glider.gol
./Debug/bin/gameOfLife -f states/space_ships/heavyWeightSpaceship.gol
./Debug/bin/gameOfLife -f states/space_ships/lightWeightSpaceship.gol
./Debug/bin/gameOfLife -f states/space_ships/middleWeightSpaceship.gol

./Debug/bin/gameOfLife -f states/still_life/bee_hive.gol
./Debug/bin/gameOfLife -f states/still_life/block.gol
./Debug/bin/gameOfLife -f states/still_life/boat.gol
./Debug/bin/gameOfLife -f states/still_life/loaf.gol
./Debug/bin/gameOfLife -f states/still_life/tub.gol
```
