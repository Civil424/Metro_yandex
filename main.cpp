#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

struct Station {
    int name;
};

struct Line
{
    int id;
    std::vector<Station> stations;

    bool operator<(const Line& other) const {
        return id < other.id;
    }
};

void input(int& allStations, int& allLines, std::vector<Line>& lines, Station& a, Station& b) {
    std::cin >> allStations;
    std::cin >> allLines;

    for (int i = 0; i < allLines; i++) {
        Line line;
        line.id = i;
        
        int stationsCount;
        std::cin >> stationsCount;
        for (int t = 0; t < stationsCount; t++) {
            Station station;
            std::cin >> station.name;
            line.stations.push_back(station);
        }
        lines.push_back(line);
    }

    std::cin >> a.name;
    std::cin >> b.name;
}

std::vector<Line> checkLines(int& allLines, std::vector<Line>& lines, Station searchStation) {
    std::vector<Line> startLines;

    for (int i = 0; i < allLines; i++) {
        Line line = lines[i];
        for (int t = 0; t < line.stations.size(); t++) {
            Station station = line.stations[t];
            if (station.name == searchStation.name) {
                startLines.push_back(line);
            }
        }
    }
    return startLines;
    
}

std::vector<Line> checkTransit(int& allLines, std::vector<Line>& lines, Line currentLine, Station searchStation) {
    std::vector<Line> transitLines;

    for (int i = 0; i < allLines; i++) {
        Line line = lines[i];
        if (line.id != currentLine.id) {
            for (int t = 0; t < line.stations.size(); t++) {
                Station station = line.stations[t];
                if(station.name == searchStation.name) {
                    transitLines.push_back(line);
                }
            }
        }
    }
    return transitLines;
}

int searchPath(int& allLines, std::vector<Line>& lines, Station& a, Station& b, Line startLine) {
    std::set<Line> visitedLines;
    std::queue<Line> linesQueue;
    std::queue<Line> bufferQueue;
    int step = 0;

    linesQueue.push(startLine);
    visitedLines.insert(startLine);

    while (linesQueue.size() != 0) {
        Line line = linesQueue.front();
        linesQueue.pop();

        for (int i = 0; i < line.stations.size(); i++) {
            Station station = line.stations[i];

            if (station.name == b.name) {
                return step;
            }

            std::vector<Line> transitLines = checkTransit(allLines,lines,line,station);
            if(transitLines.size() != 0) {
                for (int h = 0; h < transitLines.size(); h++) {
                    if (!visitedLines.count(transitLines[h])) {
                        bufferQueue.push(transitLines[h]);
                        visitedLines.insert(transitLines[h]);
                    }
                }
            }
        }

        if(linesQueue.size() == 0 && bufferQueue.size() != 0) {
            linesQueue = bufferQueue;
            bufferQueue = {};
            step++;
        }
        if (linesQueue.size() == 0 && bufferQueue.size() == 0) {
            return -1;
        }
    }
    return -1;
}

int moreLines(int& allLines, std::vector<Line>& lines, Station& a, Station& b) {
    std::vector<Line> startLines = checkLines(allLines, lines,a);
    int best = -1;

    for (int i = 0; i < startLines.size(); i++) {
        int step = searchPath(allLines,lines,a,b,startLines[i]);
        if (step == -1) continue;
        if (best == -1 || step < best) {
            best = step;
        }
    }
    return best;
}

int main() {
    int allStations = 0;
    int allLines = 0;
    std::vector<Line> lines;

    Station a;
    Station b;

    input(allStations, allLines, lines, a, b);

    int step = moreLines(allLines, lines, a, b);

    std::cout << step;
}