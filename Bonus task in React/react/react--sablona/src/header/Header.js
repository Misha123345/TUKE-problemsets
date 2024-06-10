import './Header.css'
import BottomMenu from './bottom-menu/BottomMenu';
import TopMenu from './top-menu/TopMenu';

function Header() {
    return(
    <div className="header"> 
        <div className="logo">
        <img className="logo-image" src="https://cdn.iconscout.com/icon/free/png-512/free-react-3-1175109.png?f=webp&w=256" alt="Logo" />
        </div>
        <div className="navbar">
            <TopMenu />  
            <div className="bottom-part">
                <BottomMenu />
            </div>
        </div>
    </div>
    );
}

export default Header;