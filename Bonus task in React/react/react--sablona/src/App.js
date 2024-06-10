import About from './About/About.js';
import Contacts from './Contacts/Contacts.js';
import { SearchProvider } from './ContextProvider.js';
import Home from './Home/Home.js';
import Header from './header/Header';
import ItemContainer from './item-container/ItemContainer';
import {BrowserRouter as Router, Routes, Route} from 'react-router-dom';

function App() {
  return (
    <Router>
      <div>
        <SearchProvider>
          <Header />
          <Routes>
            <Route path="/" element={<Home/>} />
            <Route path="/item-container" element={<ItemContainer />} />
            <Route path="/about" element={<About />} />
            <Route path="/contacts" element={<Contacts />} />
          </Routes>
        </SearchProvider>
      </div>
    </Router>
  );
}

export default App;


/*<div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Edit <code>src/App.js</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
      </header>
    </div>*/