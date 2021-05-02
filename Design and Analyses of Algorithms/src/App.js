import "./App.css";
import { Button, Row, Col } from "antd";
import { Link, Route } from "react-router-dom";

function App() {
  return (
    <div className="App">
      <h1>Dynamic Programming Algorithms</h1>
      <h3>Group Members</h3>
      <ol>
        <li>Mugheera Bin Sadiq ( 18K - 0296 )</li>
        <li>Yusha Arif ( 18K - 1289 )</li>
      </ol>
      <div className="Main">
        <Row>
          <Col>
            <Button type="primary" danger>
              <Link to="/LCS">Longest Common Subsequence</Link>
            </Button>
          </Col>
          <Col>
            <Button type="primary" danger>
              <Link to="/SCS">Shortest Common Supersequence</Link>
            </Button>
          </Col>
        </Row>
        <Row>
          <Button type="primary" danger>
            <Link to="/LIS">Longest Increasing Subsequence</Link>
          </Button>
          <Button type="primary" danger>
            <Link to="/ED">The Levenshtein distance (Edit distance)</Link>
          </Button>
        </Row>
        <Row>
          <Button type="primary" danger>
            <Link to="/MCM">Matrix Chain Multiplication</Link>
          </Button>
          <Button type="primary" danger>
            <Link to="/kP">0–1 Knapsack problem</Link>
          </Button>
        </Row>
        <Row>
          <Button type="primary" danger>
            <Link to="/PP">Partition problem</Link>
          </Button>
          <Button type="primary" danger>
            <Link to="/RC">Rod Cutting</Link>
          </Button>
        </Row>
        <Row>
          <Button type="primary" danger>
            <Link to="/CCP">Coin change problem</Link>
          </Button>
          <Button type="primary" danger>
            <Link to="/WBP">Word Break Problem</Link>
          </Button>
        </Row>
      </div>
    </div>
  );
}

export default App;
