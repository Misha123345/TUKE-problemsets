import { Link } from 'react-router-dom';
import './BottomMenu.css';

function BottomMenu(){
    return(
        <div className="bottom-text">
            <Link to="/">Domov</Link>
            <Link to="/item-container">Produkty</Link>
            <Link to="/about">O nás</Link>
            <Link to="/contacts">Kontakty</Link>
        </div>
    );
}

export default BottomMenu;