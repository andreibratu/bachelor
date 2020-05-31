import React from 'react';
import './NotFound.css';
import {Heading, HeadingLevel} from "baseui/heading";
import {Paragraph1} from "baseui/typography";

const NotFound = () => (
    <div className="NotFound">
        <HeadingLevel>
            <Heading>404</Heading>
            <Paragraph1>Atata s-a putut..</Paragraph1>
        </HeadingLevel>
    </div>
);

NotFound.propTypes = {};

NotFound.defaultProps = {};

export default NotFound;
