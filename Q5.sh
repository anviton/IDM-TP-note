#!/bin/bash

numReplications=10

runReplication() {
    numberRep=$1
    statusFile="./out/MTStatus-Q3-${numberRep}"
    program="./TP5"

    echo "Réplication ${numberRep} : calcul ... "
    $program 5 $statusFile >> "./res/volume_sphere-Q5-bis"
    echo "Replication ${numberRep} : terminée."
}

export -f runReplication

start=$SECONDS

for ((i = 1; i < numReplications+1; i++)); do
    runReplication $i &
done

wait

end=$SECONDS
elapsed=$((end - start))
echo "Temps total pour 10 réplications : ${elapsed} seconds."