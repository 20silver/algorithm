#include "HungarianAlgorithm.h"
// constructor 
/* cost matrix :
    i, j번째 원소는 worker i에게 할당된 작업 j의 cost (여기서 cost는 push distance인듯)
    The cost matrix must not be irregular in the sense that all rows must be the same length.
    */
HungarianAlgorithm::HungarianAlgorithm (int matrixSize)
{
    this->dim = matrixSize;
    this->rows = matrixSize;
    this->cols = matrixSize;
    // initialize costMatrix vector
    for (int i = 0; i < matrixSize; i++)
    {
        vector<double> tmp(matrixSize);
        this->costMatrix.push_back(tmp);
    }
    labelByWorker.reserve(this->dim);
    labelByJob.reserve(this->dim);
    minSlackWorkerByJob.reserve(this->dim);
    minSlackValueByJob.reserve(this->dim);
    committedWorkers.reserve(this->dim);
    parentWorkerByCommittedJob.reserve(this->dim);
    matchJobByWorker.reserve(this->dim);
    matchWorkerByJob.reserve(this->dim);

    fill(matchJobByWorker.begin(), matchJobByWorker.end(), -1);
    fill(matchWorkerByJob.begin(), matchWorkerByJob.end(), -1);
} // end constructor

// excute the algorithm
/*
    cost matrix를 기반으로 workers 와 job의 minimum cost를 계산
    a matching value of -1 indicates that the corresponding worker is unassigned
*/
vector<int> HungarianAlgorithm::execute(vector<vector<double> > costMatrix)
{
    /*
        Heuristics to improve performance :
        row와 column을 그것들의 가장 작은 원소로 reduce, 
        compute an initial non-zero dual feasible solution and create a greedy matching from workers to jobs of the cost matrix.
    */
    this->costMatrix = costMatrix;
    reduce(); 
    computeInitialFeasibleSolution();
    greedyMatch();

    int w = fetchUnmatchedWorker();
    while(w < dim )
    {
        initializePhase(w);
        executePhase();
        w = fetchUnmatchedWorker();
    }
    vector<int> result;
    result.assign(matchJobByWorker.begin(), matchJobByWorker.begin() + rows);
    for (w = 0; w < result.size(); w++)
    {
        if(result[w] >= cols)
        {
            result[w] = -1;
        }
    }
    return result;
} // end excute()

void HungarianAlgorithm::computeInitialFeasibleSolution()
{
    double inf = numeric_limits<double>::infinity(); // 양의 무한대..
    for (int j = 0; j < dim; j++)
    {
        labelByJob[j] = inf;
    }
    for (int w = 0; w < dim; w++)
    {
        for (int j = 0; j < dim; j++)
        {
            if(costMatrix[w][j] < labelByJob[j]) 
            {
                labelByJob[j] = costMatrix[w][j];
            }
        }
    }
} // end computeInitialFeasibleSolution()

/**
 * Execute a single phase of the algorithm. A phase of the Hungarian
* algorithm consists of building a set of committed workers and a set of
* committed jobs from a root unmatched worker by following alternating
* unmatched/matched zero-slack edges. If an unmatched job is encountered,
* then an augmenting path has been found and the matching is grown. If the
* connected zero-slack edges have been exhausted, the labels of committed
* workers are increased by the minimum slack among committed workers and
* non-committed jobs to create more zero-slack edges (the labels of
* committed jobs are simultaneously decreased by the same amount in order
* to maintain a feasible labeling).
* <p>
* 
* The runtime of a single phase of the algorithm is O(n^2), where n is the
* dimension of the internal square cost matrix, since each edge is visited
* at most once and since increasing the labeling is accomplished in time
* O(n) by maintaining the minimum slack values among non-committed jobs.
* When a phase completes, the matching will have increased in size.
*/

void HungarianAlgorithm::executePhase() {
    double inf = numeric_limits<double>::infinity(); 
    while (true) {
        int minSlackWorker = -1, minSlackJob = -1;
        double minSlackValue = inf;
        for (int j = 0; j < dim; j++) {
            if (parentWorkerByCommittedJob[j] == -1) {
                if (minSlackValueByJob[j] < minSlackValue) {
                    minSlackValue = minSlackValueByJob[j];
                    minSlackWorker = minSlackWorkerByJob[j];
                    minSlackJob = j;
                }
            }
        }
        if (minSlackValue > 0) {
            updateLabeling(minSlackValue);
        }
        parentWorkerByCommittedJob[minSlackJob] = minSlackWorker;
        if (matchWorkerByJob[minSlackJob] == -1) {
            /*
                * An augmenting path has been found.
                */
            int committedJob = minSlackJob;
            int parentWorker = parentWorkerByCommittedJob[committedJob];
            while (true) {
                int temp = matchJobByWorker[parentWorker];
                match(parentWorker, committedJob);
                committedJob = temp;
                if (committedJob == -1) {
                    break;
                }
                parentWorker = parentWorkerByCommittedJob[committedJob];
            }
            return;
        } else {
            /*
                * Update slack values since we increased the size of the
                * committed workers set.
                */
            int worker = matchWorkerByJob[minSlackJob];
            committedWorkers[worker] = true;
            for (int j = 0; j < dim; j++) {
                if (parentWorkerByCommittedJob[j] == -1) {
                    double slack = costMatrix[worker][j]
                            - labelByWorker[worker] - labelByJob[j];
                    if (minSlackValueByJob[j] > slack) {
                        minSlackValueByJob[j] = slack;
                        minSlackWorkerByJob[j] = worker;
                    }
                }
            }
        }
    }
} // end excutePhase()

/**
 * 
 * @return the first unmatched worker or {@link #dim} if none.
 */
int HungarianAlgorithm::fetchUnmatchedWorker() {
    int w;
    for (w = 0; w < dim; w++) {
        if (matchJobByWorker[w] == -1) {
            break;
        }
    }
    return w;
} // end fetchUnmatchedWorker()

 /**
	 * Find a valid matching by greedily selecting among zero-cost matchings.
	 * This is a heuristic to jump-start the augmentation algorithm.
	 */
void HungarianAlgorithm::greedyMatch() {
    for (int w = 0; w < dim; w++) {
        for (int j = 0; j < dim; j++) {
            if (matchJobByWorker[w] == -1
                    && matchWorkerByJob[j] == -1
                    && costMatrix[w][j] - labelByWorker[w] - labelByJob[j] == 0) {
                match(w, j);
            }
        }
    }
} // end greedyMatch()

/**
 * Initialize the next phase of the algorithm by clearing the committed
 * workers and jobs sets and by initializing the slack arrays to the values
 * corresponding to the specified root worker.
 * 
 * @param w
 *            the worker at which to root the next phase.
 */
void HungarianAlgorithm::initializePhase(int w) {
    fill(committedWorkers.begin(), committedWorkers.end(), false);
    fill(parentWorkerByCommittedJob.begin(), parentWorkerByCommittedJob.end(), -1);
    committedWorkers[w] = true;
    for (int j = 0; j < dim; j++) {
        minSlackValueByJob[j] = costMatrix[w][j] - labelByWorker[w]
                - labelByJob[j];
        minSlackWorkerByJob[j] = w;
    }
} // end initializePhase()

/**
 * Helper method to record a matching between worker w and job j.
 */
void HungarianAlgorithm::match(int w, int j) {
    matchJobByWorker[w] = j;
    matchWorkerByJob[j] = w;
} // end match()

void HungarianAlgorithm::reduce() {
    double inf = numeric_limits<double>::infinity(); 
    for (int w = 0; w < dim; w++) {
        double min = inf;
        for (int j = 0; j < dim; j++) {
            if (costMatrix[w][j] < min) {
                min = costMatrix[w][j];
            }
        }
        for (int j = 0; j < dim; j++) {
            costMatrix[w][j] -= min;
        }
    }
    double min[dim];
    for (int j = 0; j < dim; j++) {
        min[j] = inf;
    }
    for (int w = 0; w < dim; w++) {
        for (int j = 0; j < dim; j++) {
            if (costMatrix[w][j] < min[j]) {
                min[j] = costMatrix[w][j];
            }
        }
    }
    for (int w = 0; w < dim; w++) {
        for (int j = 0; j < dim; j++) {
            costMatrix[w][j] -= min[j];
        }
    }
} // end reduce()

void HungarianAlgorithm::updateLabeling(double slack) {
		for (int w = 0; w < dim; w++) {
			if (committedWorkers[w]) {
				labelByWorker[w] += slack;
			}
		}
		for (int j = 0; j < dim; j++) {
			if (parentWorkerByCommittedJob[j] != -1) {
				labelByJob[j] -= slack;
			} else {
				minSlackValueByJob[j] -= slack;
			}
        }
    } // end updateLabeling()