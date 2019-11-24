#ifndef HUNGARIANALGORITHM_H
#define HUNGARIANALGORITHM_H

#include <vector>
#include <algorithm>

using namespace std;

class HungarianAlgorithm {
    public:
         // constructor 
        /* cost matrix :
            i, j번째 원소는 worker i에게 할당된 작업 j의 cost (여기서 cost는 push distance인듯)
            The cost matrix must not be irregular in the sense that all rows must be the same length.
         */
        HungarianAlgorithm (int matrixSize);
        // excute algorithm
        vector<int> execute(vector<vector<double>> &costMatrix);

    private:
        vector<vector<double>> costMatrix;
        int rows, cols, dim;
        vector<double> labelByWorker, labelByJob;
        vector<int> minSlackWorkerByJob;
        vector<double> minSlackValueByJob;
        vector<int> matchJobByWorker, matchWorkerByJob;
        vector<int> parentWorkerByCommittedJob;
        vector<bool> committedWorkers;

        void computeInitialFeasibleSolution();
        void executePhase() ;
        int fetchUnmatchedWorker();
        void greedyMatch();
        void initializePhase(int w);
        void match(int w, int j);
        void reduce();
        void updateLabeling(double slack);
};

#endif