import React from "react"
import { Link } from "react-router-dom"
import "./Home.css"

const Home = () => {
  return (
    <div className="home">
      <h1>Home</h1>
      <button><Link to={"/item-container"}>Item Container</Link></button>
    </div> 
  )
}

export default Home