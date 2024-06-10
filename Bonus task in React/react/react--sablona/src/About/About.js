import React from "react"
import { Link } from "react-router-dom"
import "./About.css"

const About = () => {
  return (
    <div className="about">
      <h1>About</h1>
      <button><Link to={"/item-container"}>Item Container</Link></button>
    </div> 
  )
}

export default About